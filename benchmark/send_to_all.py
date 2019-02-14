# /usr/bin/env python3

import subprocess as sp
import json

test_suite = []

def sendto(addr, amount=1):
    txid = sp.run(args=["bitcoin-cli", "sendtoaddress", addr, str(amount)], stdout=sp.PIPE)
    raw = sp.run(["bitcoin-cli", "getrawtransaction", txid.stdout.strip()], stdout=sp.PIPE)
    return raw.stdout.decode().strip()

with open('wallet_list', 'r') as wallet_list, open('test_data.json', 'w') as test_data:
    fee_payment_tx = sendto("moQAM7ECkhHfcbgEhjw6eKNBtecS5XR4PG")
    for addr in wallet_list.readlines():
        (size, address) = addr.strip().split(',')

        wallet_tx = sendto(address)

        test_suite.append(dict(
            size=int(size),
            wallet_tx=wallet_tx,
            fee_payment_tx=fee_payment_tx,

        ))

    json.dump(test_suite, test_data)
