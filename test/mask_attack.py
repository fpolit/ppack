#!/usr/bin/env python3

from sbash.core import Bash

maskFile = open('john.hcmasks', 'r')

while mask := maskFile.readline():
    mask = mask.rstrip()
    mask_attack = f"john --mask={mask} --format=Raw-SHA256 crackme.txt"
    Bash.exec(mask_attack)
