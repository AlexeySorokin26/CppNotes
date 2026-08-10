Идея в том что мы хотим иметь один объект класса, который будет использоваться во всем приложении. 
Для этого мы используем паттерн Singleton, который гарантирует, что у нас будет только один экземпляр класса и предоставляет глобальную точку доступа к этому экземпляру.

class Singleton {
public:
    static Singleton& getInstance() {
        static Singleton instance;  // создаётся при первом вызове
        return instance;
    }

    // удаляем конструкторы копирования и присваивания
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton() = default;          // приватный конструктор
    ~Singleton() = default;         // можно сделать приватным, если нужен контроль
};

// Использование:
auto& s = Singleton::getInstance();