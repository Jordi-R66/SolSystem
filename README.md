# SolSystem

This project is an attempt to realize a simulator of the solar system by assuming the orbits of its objects are constant, like a track followed by each of them.

It directly relies on the code used for my TLE-Decoder repository.

## System File Composition

```csv
BodyId,BodyName,BodyParent,Mass,SMA,Ecc,Incl,LNA,PeLNG,MeanLNG
```

`Sol.system` has been made using NASA Planetary Factsheets in section Mass and J2000.0

### System Conf File

```text
NAME = Sol // Limited to 24 chars
MASS = 24 // exponent to raise 10 by, here it represents 10^24 kilograms
SMA  = 149597870700 // meters
```
