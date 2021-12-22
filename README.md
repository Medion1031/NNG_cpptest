# NNG_cpptest

## A program alapvetései
- A program megírása közben törekedtem a cleancode megtartására.
- A feladat szövege alapján illetve futási idő gyorsítása és tárhelykihasználás miatt csak a kötelező regisztereket olvastam be.
- A file neve a programba van égetve, de ezt könnyen tudnám pár perc alatt változtatni a feladat szövegezése miatt feleslegesnek tartottam.
## Beolvasás
Beolvasás során törekedtem a hibák kiszűrésére. Amikor hibás regisztert talál a beolvasó szimplán átugorja és nem dob hibát (szintén tudnék rajta változtatni csak feleslegesnek véltem a feladat szövegezése alapján).
### Hibás regisztereknek vettem a következőket:
- Nincs név illetve típus
- Az O-val jelölt utcának a kezdő vagy végpontja páros szám.
- Az E-vel jelölt utcáknak a kezdő vagy végpontja páratlan szám.