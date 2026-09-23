#pragma once
#include <vector>
#include "NPC.hpp"
#include "Item.hpp"

struct Area {
    int linha = 0;
    int coluna = 0;
    bool ativa = false;

    std::vector<NPC> inimigos;
    std::vector<Item> itens;
};
