#!/bin/bash

# =====================
# MINISHELL TEST SUITE
# =====================

# 1. Simple commands
echo -e "\n[TEST 1] Simple commands"
echo "Running: ls"
ls
echo "Running: pwd"
pwd
echo "Running: echo Hello World"
echo Hello World

# 2. Redirections
echo -e "\n[TEST 2] Redirections"
echo "Running: echo 'line 1' > test_file.txt"
echo "line 1" > test_file.txt
echo "Running: echo 'line 2' >> test_file.txt"
echo "line 2" >> test_file.txt
echo "Running: cat < test_file.txt"
cat < test_file.txt
rm test_file.txt

# 3. Pipes
echo -e "\n[TEST 3] Pipes"
echo "Running: echo 'pipe test' | grep test"
echo "pipe test" | grep test
echo "Running: ls -l | grep minishell"
ls -l | grep minishell

# 4. Heredoc test (<<)
echo -e "\n[TEST 4] Heredoc (you must manually type END to finish)"
echo "Running: cat << END"
cat << END
This is a heredoc
test input
END

# 5. Environment variables
echo -e "\n[TEST 5] Environment Variables"
echo "Running: echo \$HOME"
echo $HOME
echo "Running: echo \$PATH"
echo $PATH
echo "Running: export MYVAR=Hello"
export MYVAR=Hello
echo "Running: echo \$MYVAR"
echo $MYVAR
echo "Running: unset MYVAR"
unset MYVAR
echo "Running: echo \$MYVAR"
echo $MYVAR

# 6. Exit status
echo -e "\n[TEST 6] Exit status"
echo "Running: false"
false
echo "Running: echo \$? (should print non-zero)"
echo $?
echo "Running: true"
true
echo "Running: echo \$? (should print 0)"
echo $?

# 7. Builtins
echo -e "\n[TEST 7] Builtin commands"
echo "Running: pwd"
pwd
echo "Running: cd .."
cd ..
echo "Running: pwd"
pwd
echo "Running: cd -"
cd -
echo "Running: export TESTVAR=ok"
export TESTVAR=ok
echo "Running: env | grep TESTVAR"
env | grep TESTVAR
echo "Running: unset TESTVAR"
unset TESTVAR

# 8. Invalid commands
echo -e "\n[TEST 8] Invalid command"
echo "Running: nonexistentcommand"
nonexistentcommand
echo "Running: ./nonexistentfile"
./nonexistentfile

# 9. Quoting
echo -e "\n[TEST 9] Quoting"
echo "Running: echo \"double quotes\""
echo "double quotes"
echo "Running: echo 'single quotes'"
echo 'single quotes'
echo "Running: echo \"user is: \$USER\""
echo "user is: $USER"
echo "Running: echo 'user is: \$USER'"
echo 'user is: $USER'

# 10. Logic ops (bonus only)
echo -e "\n[TEST 10] Logic operators (only if bonus implemented)"
echo "Running: true && echo 'Success'"
true && echo "Success"
echo "Running: false || echo 'Recovered'"
false || echo "Recovered"
echo "Running: false && echo 'Won\'t print'"
false && echo "Won't print"
echo "Running: true || echo 'Won\'t print'"
true || echo "Won't print"

# End
echo -e "\n✅ All tests executed. Check outputs above."

