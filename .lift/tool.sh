#!/usr/bin/env bash

#dir=$1
#commit=$2
cmd=$3

function run() {
    curl -LO https://github.com/hth313/lift-whitespace/releases/download/0.9.1/lift-whitespace
    chmod +x lift-whitespace
    ./lift-whitespace $(git ls-files | grep -v lift)
}

[[ "$cmd" = "version" ]] && echo "1"
[[ "$cmd" = "applicable" ]] && echo "true"
[[ "$cmd" = "run" ]] && run
[[ -z "$cmd" ]] && echo '{ "version" : 1, "name" : "lift-whitespace" }'

# exit code 0, we always succeed if we got this far
:
