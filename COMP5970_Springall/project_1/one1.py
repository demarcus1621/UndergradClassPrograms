#!/usr/bin/python
# -*- coding: utf-8 -*-
blob = """            ��t�;O�G�o�rXƿN�3:��4u��
޷��������O��į��)+f�he�#�ӂ�sJ������!���FeV�Y�v	��OL���$�
������kY�z?�DR�yl����<��*"""
from hashlib import sha256
print sha256(blob).hexdigest()