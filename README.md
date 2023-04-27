# 💎 DPXCLI
command line utility for interacting with DPX API

## ✨ Examples

### Help
Description: shows the help menu  
Usage: `dpxcli help`
```text
$ dpxcli help
```

### Balance
Description: retrieves the balance of the wallet  
Usage: `dpxcli balance -w|--wallet <wallet>`
```text
$ dpxcli balance --wallet ADDRESS
```

### Transfer
Description: transfers specified amount of DPX from departure wallet to destination wallet  
Usage: `dpxcli transfer -a|--amount <amount> -w|--wallet <wallet> -s|--secret <secret> -d|--destination <destination>`
```text
$ dpxcli transfer --amount 10.5 --wallet ADDRESS --secret SECRET --destination ADDRESS
```

### Transactions
Description: retrieves transactions in descending order from specified offset (default is 0)  
Usage: `dpxcli transactions (-o|--offset <offset>)? (-w|--wallet <departure>)? (-d|--destination <destination>)?`
```text
$ dpxcli transactions // show latest 256 transactions
$ dpxcli transactions --offset 128 // show from offset 128
$ dpxcli transactions --wallet ADDRESS // filter transactions that are from this departure
$ dpxcli transactions --destination ADDRESS // filter transactions that are to this destination
$ dpxcli transactions -o 64 -w DEPARTURE -d DESTINATION // filter transactions that are from DEPARTURE to DESTINATION and show from offset 64
```

### Transaction
Description: retrieves information of the given transaction id  
Usage: `dpxcli transaction -i|--id <transactionId>`
```text
$ dpxcli transaction --id TRXID
```

### Revoke
Description: revokes the secret of the wallet and returns the new secret  
Usage: `dpxcli revoke -w|--wallet <wallet> -s|--secret <secret>`
```text
$ dpxcli revoke --wallet ADDRESS --secret SECRET
```

### Verify
Description: verifies a wallet credentials  
Usage: `dpxcli verify -w|--wallet <wallet> -s|--secret <secret>`
```text
$ dpxcli verify --wallet ADDRESS --secret SECRET
```

## ⌛️ Install

### Linux
It's quite easy to compile the C soruce with GCC:
```text
gcc dpxcli.c -lcurl -ljson-c -o dpxcli
```
or even to make it easier, there is an script for compilation and installation:
```text
sudo ./install-linux.sh
```

### Windows
No instructions yet, though you are more than welcome to use Cygwin and compile with `-lcurl` and `-ljson-c` and help us complete the documentation.

## ⚙️ Prerequisites
Development library files of libcurl (e.g. `libcurl4-openssl-dev` or `libcurl4-gnutls-dev`) are needed for `curl/curl.h`, also the json-c library (e.g. `libjson-c-dev`) is needed for `json-c/json.h`, and that's all.

## ⚡ DPX API Documentation
Soon

## ✅ TODO
- [ ] Commentify the code for better readability  
- [ ] Create a MakeFile for build systems  
- [ ] Github actions build & test pipeline  

## 🖊️ Contribution
Your contribution to dpxcli development is very welcome!

You may contribute in the following ways:

- Report issues and feedback
- Submit fixes, features via Pull Request
- Write/polish documentation

## 📃 License
GNU Affero General Public License v3.0 see https://www.gnu.org/licenses/agpl-3.0.en.html