import cryptography.hazmat.primitives.asymmetric.ed25519 as crypto
from cryptography.hazmat.primitives import serialization

mensagem = "my authenticated message"

private_key = crypto.Ed25519PrivateKey.generate()
public_key = private_key.public_key()
print(public_key)
public_key = public_key.public_bytes(
    encoding=serialization.Encoding.Raw, format=serialization.PublicFormat.Raw
)
print(public_key)
# print(public_key.decode())
signature = private_key.sign(mensagem.encode())
# Raises InvalidSignature if verification fails
public_key = crypto.Ed25519PublicKey.from_public_bytes(public_key)
public_key.verify(signature, mensagem.encode())
