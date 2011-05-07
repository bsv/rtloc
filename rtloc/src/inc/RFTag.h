#ifndef RFTAG_H_
#define RFTAG_H_

#include "map_item.h"
#include <QString>

class RFTag : public MapItem
{
public:
    RFTag();
    RFTag(QString name_new, int x_new, int y_new);
    virtual ~RFTag();

    void setId(QString id_new);
    QString getId();
    void setRSSI(int rssi_new);
    int getRSSI();
    virtual void draw(GLWidget * w);

private:
    QString id;
    int rssi;
};

#endif /* RFTAG_H_ */
