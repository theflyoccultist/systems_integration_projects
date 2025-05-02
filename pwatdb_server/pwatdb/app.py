from fastapi import FastAPI, Request, HTTPException
import hmac
import hashlib

app = FastAPI()


def calc_digest(key, message):
    key = bytes(key, 'utf-8')
    message = bytes(message, 'utf-8')
    dig = hmac.new(key, message, hashlib.sha256)
    return dig.hexdigest()


@app.post("/verify")
async def verify_signature(request: Request):
    body = await request.json()
    recieved_mac = request.headers.get("X-HMAC-Signature")

    if not recieved_mac:
        raise HTTPException(status_code=400, detail="Missing HMAC header")

    msg_string = f"{body['mac_address']}:{body['timestamp']}"
    expected_mac = calc_digest('secret-key', msg_string)

    if not hmac.compare_digest(recieved_mac, expected_mac):
        raise HTTPException(status_code=403, detail="Invalid signature")

    return {"status": "Verified"}
