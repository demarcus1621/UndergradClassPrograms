#!/usr/bin/python
# -*- coding: utf-8 -*-
blob = """            ��t�;O�G�o�rXF�N�3:��4u��
޷�������O��į��)+f�he�#�ӂ�sJ������!���Fe��Y�v	��OL���$�
������kY��y?�DR�yl������*"""
from hashlib import sha256
print sha256(blob).hexdigest()