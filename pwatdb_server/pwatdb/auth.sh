#!/bin/bash

MAC="12:34:56:78:9a:bc"
TIME="2025-04-30T15:00:00"
MESSAGE="$MAC:$TIME"
JSON="{\"mac_address\":\"$MAC\",\"timestamp\":\"$TIME\"}"

SIGNATURE=$(echo -n "$MESSAGE" | openssl dgst -sha256 -hmac "secret-key" | sed 's/^.* //')

curl -X POST http://127.0.0.1:8000/verify \
  -H "Content-Type: application/json" \
  -H "X-HMAC-Signature: $SIGNATURE" \
  -d "$JSON"
