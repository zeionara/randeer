long randomizerSeed = 17;
long lastNumber = randomizerSeed;

long random() {
    lastNumber = lastNumber * 25214903917 + 11;
    return lastNumber;
}
