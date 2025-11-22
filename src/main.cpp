//System zarządzania jednostek bojowych w grze
//Definicja klasy bazowej
//  Klaasa bazowa Unit
//      Powinna zawierać podstawowe statyski: std::string name, int health, int attack.
//      Dodaj czysto wirtualną metodę virtual int calculate_demage() const = 0
//      Dodaj wirtualny destruktor (virtual ~Unit() = default
//  Klasy pochodne: Stworz 2-3 klasy konkretne klasy dziedziczące po Unit, np:
//      Knight: Nadpisuje calculat_damage() zwracając stałą wartość ataku.
//      Mage: Nadpisuje calculate_damage(). Wprowadza element losowy, np. zwraca atttack + random_number % 10.

//Menadzer sceny i kontenery stl, stwórze menadżera do przechowywania i przetwarzania jednostek.
//  Klasa CombatMenager:
//      Pamięć (storage): Użyj std::vector<std::unique_ptr<Unit>> do bezpiecznego prechowywania wszystkich jednostek na "scenie"
//      bo pozwala automatycznie zarządzać pamięcią (RAII) i pozwala na perzechowywanie w wektorze obiektów bazowych (polimorfizm)
//  Metody podstawowe:
//      void addUnit(std::uniqur_ptr<Unit> unit: Dodaje jednostkę
//      coid listUnit() const: Wypissuje statystyki wszystkich jednostek.
//      void simulateAttack(): Symuluje atak losowej jednostki na inną losową jednostkę ( użyj std::uniform_int_distribution z <random>).

//Analiza danych(algorytmy stl) wykorzystaj analizy do szybkiej analizy stanu pola bitwy
//  Najsilniejsza jednostka, dodaj metodę void findStrongestUnit(), która:
//      Używa algorytmu std::max_element z lambdą, aby znaleźć jednostkę z najwyższą statyską attack.
//  Średnia życia: Dodaj metodę void calculatAvarageHealth() która:
//      Używa algoryrmu std::accumulate do sumowania gealth wszystkich jednostek, a następnie dzieli przez liczbę jednostek.
//  Filtracja Jednostek gotowych do Walki: Dodaj metodę void listHealthyUnits(int minHealth), która:
//      Używa std::copy_if lub (jeśli masz C++20/23) Ranges (std::views::filter), aby skopiować i wypisać tylko te jednostki których health jest powyżej podanego progu.

//Ulepszenia i c++23 dodajj nowoczesne funkcjie języka
//  Statyczna Weryfikacja Typu: W klasie mage lub innej, dodaj nową metodę (np. castSpell()). Wmain lub CombatManage użyj dynamic_cast lub std::holds_alternative
//  (jeśli używasz std::variant) do sprawdzenia, czy jednostka jes Magiem, zanim wywołasz tę metodę.
//  C++23 zmień niektóre funkcjie na const i upenij się, że używasz [[nodiscard]] tam, gdzie ma to sens (np. w calculateDamage(), aby uniknąć ignorowania wartości zwracania.
//  Aliasy typów: użyj using unitPtr = std::unique_ptr<Unit>; dla lepszej czytelności kodu w CombatManager.

//Interakcjia w terminalu: uruchom symulacjie w terminalu.
//  Menu: ustaw proste menu w pętli: add knight/ mage/ archer, list strongest, avgHp, simulae, exit.
// Symulacjia: Użyj pętli for lub algorytmu, aby w każdej turze symulacji losowo wywłać simulatAttack().
// Wizualizacjia: Użyj prostej formatki wyjściowej np std::cout do wyświetlanie wyniku każdej akcji, np. "Knight attacs Mage for 15 damage. Mage's HP is now 5


#include <iostream>
#include <memory>
#include <string>
//#include <vector>
#include <random>

class Unit {
public:
    Unit() = default;
    Unit(const std::string& name, int health, int attack) : name_{name}, health_{health}, attack_{attack}
    {}
    virtual ~Unit() = default;
    virtual int calculateDamage() = 0;

    virtual std::string getName() const = 0;
protected:
    std::string name_{"Rysio"};
    int health_{100};
    int attack_{100};
};

class King : public Unit {
public:
    King() = default;
    King(const std::string& name, int health, int attack, const std::string& sord) : Unit{name, health, attack}, sord_{sord}
    {}
    ~King() override = default;
    std::string getName() const override { return name_; }
    int calculateDamage() override { return attack_; }
    std::string getSord() const { return sord_; }

private:
    std::string sord_{"sord"};
};

class Mage : public Unit {
public:
    Mage() = default;
    Mage(const std::string& name, int health, int attack, const std::string& spel) : Unit{name, health, attack}, spel_{spel}
    {}
    ~Mage() override = default;

    std::string getName() const override { return name_; }
    int calculateDamage() override {
        const auto randomAttack{randomSpelAttack()};
        return attack_ + randomAttack;
    }
    std::string getSpel() const { return spel_; }
    [[nodiscard]] int randomSpelAttack() {
        constexpr int start{1};
        constexpr int end{10};
        std::uniform_int_distribution distribution{start, end };
        return distribution( gen_ );
    }
private:
    std::string spel_{"spel"};
    std::random_device rd_;
    std::mt19937 gen_{rd_()};
};

int main() {
    auto king = std::make_unique<King>("Ryszard", 100, 15, "Szarpacz");
    auto mag = std::make_unique<Mage>("Gandalf", 100, 20, "Fire");
    std::cout << king->getName() << " " << king->calculateDamage() << " " << king->getSord() << '\n';
    std::cout << mag->getName() << mag->calculateDamage() << mag->getSpel() << '\n';
return 0;
}