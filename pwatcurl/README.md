🔧 Install the libcurl Development Package

Run this in your terminal:

```bash
sudo apt update
sudo apt install libcurl4-openssl-dev
```

Once that’s done, you’ll be able to compile your code like this:

```bash
clang pwatcurl.c -o pwatcurl -lcurl
```

Or use gcc, if you're not doing the Clang-core thing:

```bash
gcc pwatcurl.c -o pwatcurl -lcurl
```
