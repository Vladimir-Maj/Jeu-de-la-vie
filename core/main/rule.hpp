class Rule {
  private:
    int naissanceMin;
    int naissanceMax;
    int survieMin;
    int survieMax;

  public:
    Rule() : naissanceMin(0), naissanceMax(0), survieMin(0), survieMax(0) {};

    Rule(int nMin, int nMax, int sMin, int sMax)
        : naissanceMin(nMin), naissanceMax(nMax), survieMin(sMin),
          survieMax(sMax) {};

    // bool mustBeBorn(int countNeighbors) {};
    // bool mustSurvive(int countNeighbors) {};
    // bool apply(bool state, int countNeighbors) {};
};