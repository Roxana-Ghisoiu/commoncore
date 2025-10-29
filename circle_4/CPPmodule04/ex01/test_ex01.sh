#!/usr/bin/env bash
set -euo pipefail

# Configuration
NAME="brainAnimal"            # your executable name
BIN="./$NAME"
LOG_DIR="test_logs"
OUT="$LOG_DIR/out.txt"
MEMLOG="$LOG_DIR/memcheck.txt"

mkdir -p "$LOG_DIR"

# la începutul scriptului
CLEAN_AFTER=${CLEAN_AFTER:-0}
if [[ ${1:-} == "--clean" ]]; then CLEAN_AFTER=1; fi


note()  { printf "➡️  %s\n" "$*"; }
ok()    { printf "✅ %s\n" "$*"; }
fail()  { printf "❌ %s\n" "$*" >&2; exit 1; }

need() {
  command -v "$1" >/dev/null 2>&1 || fail "Command '$1' not found. Please install it or adjust the script."
}

# Build if the binary is missing
if [[ ! -x "$BIN" ]]; then
  note "Binary '$BIN' not found. Building with make..."
  need make
  make -j || make
  [[ -x "$BIN" ]] || fail "Build did not produce '$BIN'."
fi

# Run and capture output
note "Running $BIN ..."
set +e
"$BIN" | tee "$OUT"
run_rc=$?
set -e
[[ $run_rc -eq 0 ]] || fail "Program exited with code $run_rc. See $OUT."

# Assertion helpers
assert_contains() {
  local needle="$1"
  local msg="$2"
  if grep -F -q "$needle" "$OUT"; then
    ok "$msg"
  else
    fail "Missing: $needle  ($msg) — see $OUT"
  fi
}

assert_count_ge() {
  local needle="$1"
  local expected="$2"
  local found
  found=$(grep -F -c "$needle" "$OUT" || true)
  if (( found >= expected )); then
    ok "'$needle' appears $found times (>= $expected)"
  else
    fail "Expected at least $expected occurrences of '$needle', found $found"
  fi
}

note "Checking functional assertions..."

# 1) Subject & 50/50 array ran
assert_contains "=== Array of Animal* (half Dogs / half Cats) ===" "50/50 Animals test ran"
assert_contains "Woof"  "Dogs produce the correct sound"
assert_contains "Meow"  "Cats produce the correct sound"

# 2) Destructors (deleting via Animal*)
assert_count_ge "[Dog] Destructor called"    1
assert_count_ge "[Cat] Destructor called"    1
assert_count_ge "[Brain] Destructor called"  2   # there will be more; 2 is a safe minimum

# Your Animal message is "[Animal] dctor" — accept either that or a more verbose form
if grep -E -q "\[Animal\].*(dctor|Destructor)" "$OUT"; then
  ok "Animal destructor was invoked (virtual ~Animal())"
else
  fail "Did not detect Animal destructor (looking for '[Animal] dctor' or 'Destructor')."
fi

# 3) Deep copy signals
assert_contains "[Dog] Copy constructor called"         "Dog copy-ctor was called"
assert_contains "[Cat] Copy assignment operator called" "Cat copy-assignment was called"
assert_contains "[Brain] Copy constructor called"       "Brain is being copied (deep copy), not shared"

ok "All functional assertions passed 🎉"
echo

# Memory checks (optional)
if [[ "${NO_MEMCHECK:-0}" == "1" ]]; then
  note "Memcheck disabled (NO_MEMCHECK=1)."
  exit 0
fi

note "Attempting memcheck (valgrind on Linux, leaks on macOS, if available)..."

OS=$(uname -s || echo "Unknown")

if [[ "$OS" == "Darwin" ]] && command -v leaks >/dev/null 2>&1; then
  set +e
  leaks -atExit -- "$BIN" 2>&1 | tee "$MEMLOG"
  leaks_rc=${PIPESTATUS[0]}
  set -e
  if [[ $leaks_rc -eq 0 ]]; then
    ok "leaks: no memory leaks reported"
  else
    fail "leaks reported memory leaks. See $MEMLOG"
  fi
elif command -v valgrind >/dev/null 2>&1; then
  set +e
  valgrind --leak-check=full --show-leak-kinds=all --error-exitcode=42 --quiet "$BIN" 2> "$MEMLOG"
  vg_rc=$?
  set -e
  if [[ $vg_rc -eq 0 ]]; then
    ok "valgrind: no memory leaks reported"
  else
    echo "–––– Valgrind output ––––"
    cat "$MEMLOG" || true
    fail "valgrind reported leaks/errors"
  fi
else
  note "Neither 'valgrind' (Linux) nor 'leaks' (macOS) found. Skipping memcheck."
fi

ok "All tests + memcheck completed successfully ✅"

# la final, după memcheck și mesaje de succes
if [[ "$CLEAN_AFTER" == "1" ]]; then
  note "Cleaning test logs ($LOG_DIR)..."
  rm -rf -- "$LOG_DIR"
fi

