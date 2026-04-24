// Problems

// 🔴 Код создания врагов дублируется в 10 разных местах

// 🔴 Чтобы добавить нового врага (например, Medic), нужно лезть во все эти места

// 🔴 Легко ошибиться — где-то забыть инициализировать здоровье

// 🔴 if-else каша, код раздувается

class Game {
public:
    void spawnEnemy(std::string type, int x, int y) {
        Enemy* enemy = nullptr;
        
        // ВСЯ логика создания прямо здесь!
        if (type == "pilot") {
            enemy = new Pilot(x, y);
            enemy->setHealth(100);
            enemy->setWeapon("пистолет");
        } 
        else if (type == "tank") {
            enemy = new Tank(x, y);
            enemy->setHealth(500);
            enemy->setWeapon("пушка");
        }
        else if (type == "sniper") {
            enemy = new Sniper(x, y);
            enemy->setHealth(80);
            enemy->setWeapon("винтовка");
        }
        
        enemies.push_back(enemy);
        // ... много другой логики
    }
    
    void respawnEnemy(Enemy* deadEnemy) {
        // ОПЯТЬ та же логика создания!
        if (deadEnemy->getType() == "pilot") {
            Enemy* newEnemy = new Pilot(deadEnemy->getX(), deadEnemy->getY());
            // ... инициализация
        }
        else if (deadEnemy->getType() == "tank") {
            // ... снова if-ы
        }
        // И так в 10 местах!
    }
    
private:
    std::vector<Enemy*> enemies;
};

// First idea to solve

class Level1 {
    void createEnemies() {
        // Прямое создание конкретных классов
        Pilot* p = new Pilot(10, 20);
        p->setHealth(100);
        Tank* t = new Tank(30, 40);
        t->setHealth(500);
        
        // Ой, а что если в Level2 нужно создать тех же врагов, но с другими параметрами?
        // Придется копировать код!
    }
};

class Level2 {
    void createEnemies() {
        // Снова копипаста, только здоровье другое
        Pilot* p = new Pilot(10, 20);
        p->setHealth(150);  // !!! Другое значение
        Tank* t = new Tank(30, 40);
        t->setHealth(600);
        
        // А если логика создания сложнее? Будет кошмар
    }
};


// Beter solution

// 1. Абстрактная фабрика (интерфейс)
class EnemyFactory {
public:
    virtual Enemy* create(int x, int y) = 0;
    virtual ~EnemyFactory() = default;
};

// 2. Конкретные фабрики для каждого типа врага
class PilotFactory : public EnemyFactory {
public:
    Enemy* create(int x, int y) override {
        Pilot* pilot = new Pilot(x, y);
        pilot->setHealth(100);
        pilot->setWeapon("пистолет");
        return pilot;
    }
};

class TankFactory : public EnemyFactory {
public:
    Enemy* create(int x, int y) override {
        Tank* tank = new Tank(x, y);
        tank->setHealth(500);
        tank->setWeapon("пушка");
        return tank;
    }
};

// 3. Теперь Game работает через фабрику
class Game {
public:
    void setEnemyFactory(EnemyFactory* factory) {
        this->factory = factory;
    }
    
    void spawnEnemy(int x, int y) {
        // Не знает, какой именно враг создается!
        Enemy* enemy = factory->create(x, y);
        enemies.push_back(enemy);
        
        // Вся остальная логика та же
        enemy->spawnAnimation();
    }
    
    void respawnEnemy(Enemy* deadEnemy) {
        // Переиспользуем ТУ ЖЕ фабрику!
        Enemy* newEnemy = factory->create(deadEnemy->getX(), deadEnemy->getY());
        // ... остальная логика
    }
    
private:
    EnemyFactory* factory;
    std::vector<Enemy*> enemies;
};

// Hot to use it
int main() {
    Game game;
    
    // Для уровня 1 - создаем пилотов
    PilotFactory pilotFactory;
    game.setEnemyFactory(&pilotFactory);
    game.spawnEnemy(10, 20);  // Создаст пилота
    
    // Для уровня 2 - создаем танки
    TankFactory tankFactory;
    game.setEnemyFactory(&tankFactory);
    game.spawnEnemy(30, 40);  // Создаст танк
    
    // Легко добавить нового врага!
    // Просто пишем новый класс фабрики, остальной код не трогаем
}