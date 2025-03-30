#!/bin/bash

echo -e "\n[TEST 1] Prompt Display"
echo "You should see the custom minishell prompt."

echo -e "\n[TEST 2] History Support"
echo "Type a few commands (like: ls, pwd), then press ↑ arrow key."

echo -e "\n[TEST 3] Executables via PATH"
echo "Running: ls"
ls
echo "Running: whoami"
whoami
echo "Running: echo Hello Minishell"
echo Hello Minishell

echo -e "\n[TEST 4] Absolute Path Execution"
echo "Running: /bin/ls"
 /bin/ls
echo "Running: /usr/bin/env"
/usr/bin/env
echo "Running: /usr/bin/whoami"
/usr/bin/whoami

echo -e "\n[TEST 5] Relative Path Execution"
echo "Running: ./minishell (new instance, type 'exit' to return)"
./minishell

echo -e "\n[TEST 6] Invalid Command"
echo "Running: commandnotfound"
commandnotfound

echo -e "\n✅ Done - You can copy results now."
