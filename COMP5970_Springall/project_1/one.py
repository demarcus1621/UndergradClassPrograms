#!/usr/bin/python3
# -*- coding: latin-1 -*-
blob = """         vS>�$@��6�?熜�{.�j��?�:���)��޶�
�0�:�a�]3)[�)Ȗ~թ]i�uŖ��6���s�3~��Ƀ�Ƈd\�؋�0ȇ_���Պ���yE�{%\����;��Y)��fx�"""
from hashlib import sha256
print(sha256(blob.encode()).hexdigest())

if sha256(blob.encode()).hexdigest() == "f5dbe83e01c0267cf510f5d457771e3c454700ce41e703712bdd396e73fa00d5":
    print("Hashing is not encryption!")
else:
    print("Security through obscurity!")