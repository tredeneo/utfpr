from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import serialization

private_key = rsa.generate_private_key(
    public_exponent=65537, key_size=2048, backend=default_backend()
)
falsa_privada = rsa.generate_private_key(
    public_exponent=65537, key_size=2048, backend=default_backend()
)
public_key = private_key.public_key()
falsa_publica = falsa_privada.public_key()


# private_key = ...  # Placeholder - you generated this before

password = "eu um carro vermelho e preto que anda bem devagar"
message = b"encrypt me!"

print(f"privado \n{private_key}\n\n")
encrypted = falsa_privada.sign(
    message,
    padding.PSS(
        mgf=padding.MGF1(algorithm=hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH
    ),
    hashes.SHA256(),
)

# encrypted = ... # From before (could have been stored then read back here)
print(f"publica \n{public_key}\n\n")
original_message = public_key.verify(
    encrypted,
    message,
    padding.PSS(mgf=padding.MGF1(hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH),
    hashes.SHA256(),
)
