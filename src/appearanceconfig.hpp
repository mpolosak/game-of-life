class AppearanceConfig
{
public:
    void setColours();
    std::string getColours(){return coloursString};
    unsigned short liveCellColour;
    unsigned short deathCellColour;
    unsigned short backgroundColour;
private:
    std::string coloursString;
}

std::ostream& operator<<(std::ostream& os, cont AppearanceConfig& config);