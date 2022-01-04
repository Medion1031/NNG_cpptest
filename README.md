# NNG_cpptest
## Előszó
Ez a kis leirat nem az egyes függvények kielemzésére szolgál, hanem inkább a fejlesztés alatt felmerülő gondolatokat és döntéseket igyekszik tisztázni, hogy mit miért úgy csináltam ahogy.
## A program alapvetései
Alapvetően a programot törekedtem a CleanCode alapelveknek megfelelően írni illetve minnél modulárisabbá tenni, arra gondolva, hogy ezt akár egy nagyobb projekt részeként is lehessen alkalmazni.

> Néhány helyen (ezekre később térek ki sajnos meg kellett szegjem a CleanCode alapvetéseit)

## A program felépítése
A projektben 5 file található

- main.cpp
- reader.cpp -> reader.h
- geodata.cpp -> geodata.h

> Ezekre egyesével ki fogok térni mit csinálnak a továbbiakban.
 ---
 ## Fileok felépítése és működése
 A projektben lévő fileok csőrendszerben követik egymást, ezzel egyszerüsítve a fordítást és könnyebbé téve az `include` metódusokat. A fileokat a csőrendszerben lévő sorrendjükben fogom bemutatni.
 
 ### main.cpp
 Erről a fileről lehet a legkevesebb dolgot írni mivel csak egy `start()` metódust tartalmaz ami csinál valamit. A `start()` végigfuttatja a `Reader` Class metódusait a kiválasztott fileon, ezután az ebből kinyert adatot továbbadja a feldolgozó függvényemnek.
 
 ### reader.cpp illetve reader.h
 Ebben a fileban találhatoó a `Reader` Class. Inicializáláskor a beolvasandó file nevét kell neki megadni amit azonnal tárol, ezt természetesen egy egyszerű függvénnyel meg lehetne változtatni.
 ~~~cpp
 std::string getFileName() {
    std::string fileName{};
    
    std::cout << "Enter the name of the file: ";
    std::cin >> fileName;
    
    return fileName;
 }
 
 Reader::Reader() {
    std::string str = getFileName();
    _file.open(str);

    if(_file.fail()) {
        throw FILE_NOT_FOUND;
    }
}
 ~~~
 Ezután a `start()` ellenőrzi, hogy üres-e a file, ha nem akkor beolvassa az első sort a `next()` metódussal, ezt fogjuk alkalmazni az egész file beolvasására. A `next()` futása közben az `end()` függvény adja vissza, hogy vannak e még sorok a fileban, viszont ezt a `checkStatus()`˙ellenőrzi. Miközben végigfut a fileon a megfelelő helyre berakja a páros és páratlan házszámokat, ha nincs még az adott utcának reprezentatívája akkor létrehoz egyet, ebben a folyamatban a `searchForStreetIndex()`, `processLine()`, `createStreet()`, `lineSplit()`,` checkEmpty()`, `intPairToStreet()` illetve `checkRoadsAreEmpty()` segítenek. <br> 
 Egy sor feldolgozásánál csak specifikus adattagokat veszek ki soronként a feladata leírása miatt.
 <br>Van a fileban viszont 3 olyan függvény ami más alkalmazási formában nem ide kerülne, ezek a `checkElementIfTrue()`, `printVectorIfTrue()`, és `processData`. Ezek a lefutás után az adatok feldolgozásáért illetve kiiratásáért felelősek (pontosabban a `GeoData` függvényeivel ellenőrzik az adatot illetve dolgoznak vele). 
 ### geodata.cpp illetve geodata.h
  Először is ami a legfontosabb ebben a fileban van az összes `include` mivel ez van a legvégén a csőrendszernek, illetve itt van az a `structom` is amely az egész programon végig reprezentálva van.
 ~~~cpp
 struct Street {
    int start;
    int end;
};
 ~~~
 Ehhez kellett írjak `==` illetve `!=` operátorokat, mivel máshogy a vektorműveletekkel nem működött. A `Street` azért jött létre, hogy átláthatóbbá tegye a kódot, teknikailag ezt használom `std::tuple<int, int>`-ök helyett. <br><br>
 Ami a projektem lényege volt az a következő függvényekben található:
 ~~~cpp
 std::vector<Street> overlaps(const std::vector<Street> & _baseVector);
 void searchOverlaps(const int i,const std::vector<Street> baseVector);
 Street detectSegment(const Street & baseStreet, const Street iterateStreet);
 void simplify();
 void connectPairs();
 ~~~
 Az adattfeldolgozás a efnt látható sorrendben zajlik le. Ezt azért szeparáltam ennyire szét, hogy ha nem ennyire specifikusan kellene orvosolni ezt a problémát, hanem más nagyobb projektben kéne hasznosítani, akkor könnyebben átlátható illetve felhasználható legyen. <br><br>
 Ebben a fileban van megszedve 2 helyen is a CleanCode alapelve pontosabban a `connectPairs()` illetve a `checkSegment()` függvényekben, ez azért van mert a ezek nem konstans adatokkal dolgoznak, így nem lehet switchel megoldani (legalábbis én nem találtam rá módot).
