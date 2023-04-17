#include "parsetext.h"

ParseText::ParseText(QString txt)
{
    str = txt;
}

QString ParseText::parse(){

    while(1){
        if (str == "RUB") return "₽";
        else if (str == "EUR") return "€";
        else if (str == "PROM") return "‰";
        else if (str == "COPY") return "©";
        else { return 0; }
    }
}
