#include "../struct/enemy.h"

class ErrorTime : public Enemy
{
private:
    void getMovePosition() override;

public:
    ErrorTime(std::shared_ptr<nightDB> data, size_t ID);

    void joke();

    bool move(bool doorStatus) override;
};