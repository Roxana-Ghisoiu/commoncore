#!/bin/bash

# =====================================
# Script: install_readline_local.sh
# Installs GNU Readline locally in user folder
# Location: ~/minishell_project/scripts/
# =====================================

set -e

PREFIX="$HOME/.local/pkg/readline"
VERSION=8.2

# Create scripts folder if it doesn't exist
mkdir -p "$HOME/minishell_project/scripts"

if [ "$(uname -s)" == 'Darwin' ]; then
	cd /private/tmp
else
	cd /tmp
fi

echo ':: Cleaning previous build if any'
rm -rf "readline-$VERSION"
rm -rf "$PREFIX"

echo ':: Downloading GNU Readline v$VERSION'
curl -# "https://ftp.gnu.org/gnu/readline/readline-$VERSION.tar.gz" | tar xzf -

echo ':: Building and installing locally to $PREFIX'
cd "readline-$VERSION"
./configure --prefix="$PREFIX"
make -j$(nproc)
make install-static

echo ':: Cleanup temporary build files'
cd ..
rm -rf "readline-$VERSION"

echo
echo '✅ Readline installed locally in:' "$PREFIX"
echo 'Add the following flags to your Makefile:'
echo
printf "CFLAGS += -I%s/include\n" "$PREFIX"
printf "LDFLAGS += -L%s/lib -lreadline\n" "$PREFIX"
echo

