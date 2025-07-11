# SolSystem

This project is an attempt to realise a simulation of the solar system by assuming the orbits of its objects are constant, like a track followed by each of them. This approach is not valid for Mercury as its orbit fluctuates due to its proximity to the Sun. Don't use this program for real world applications.

It directly relies on the code used for my TLE-Decoder repository.

## System File Composition

```csv
BodyId,BodyName,BodyParent,Mass,SMA,Ecc,Incl,LNA,PeLNG,MeanLNG
```

Every body except Ceres has been filled using [NASA Planetary Factsheets](https://nssdc.gsfc.nasa.gov/planetary/factsheet/) in section Mass and J2000.0 considered as 01/01/2000 @ 12:00:00 TT.

Ceres' J2000 have been calculated based on the informations described on the [French Wikipedia page](https://fr.wikipedia.org/w/index.php?title=(1)_C%C3%A9r%C3%A8s&oldid=227069149)

Here is the detail of the calculation

$$
a = 2.7666197 \times 149597870700 = 41~388~016~156.67278 \text{ meters}
$$

$$
\mu = G \times (M_{Sun} + M_{Ceres}) = 6.67428 \times 10^{-11} \times (1.9884 \times 10^{30} + 9.46 \times 10^{20}) = 1.3271138358313868 \times 10^{20} \text{ m}^3/\text{s}^2
$$

$$
\Delta T = 2460600.5 - 2451545.0 = 9055.5 \text{ julian days}
$$

$M_0 = 145.84897 \text{ degs}$ (Mean anomaly given on wikipedia)

$$
n = \sqrt{\frac{\mu}{a^3}} = \sqrt{\frac{1.3271138358313868 \times 10^{20}}{(41~388~016~156.67278)^3}} \times 86400 \times \frac {180}{\pi} = 6.772960587761277 \text{ deg.day}^{-1}
$$

$$
M_{J2000} = (145.84897 - (n \times \Delta T)) \mod 360 = (145.84897 - 61332.54460247225) \mod 360 \approx 6.3454032 \text{ degs}
$$
