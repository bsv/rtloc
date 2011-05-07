#include "inc/processor.h"
#include <QMessageBox>
#include <QDebug>

Processor::Processor(QObject *parent)
	: QObject(parent)
{
    wi = new wlanapi();
}

/**
 * Вычисляем положение объекта
 * Обнавляем значения мощности сигнала
 * для активных точек в all_tags
 */
void Processor::calcPos(TagList * all_tags)
{

}

Processor::~Processor()
{
    delete wi;
    clearTagList();
}

Man * Processor::getMan()
{
    return &man;
}

TagList * Processor::getActiveTags()
{
    RFTag * tag;

    clearTagList();

    try {
        wi->get_adapter_list();
        const AP_LIST &ap_list = wi->get_ap_list(NULL);

        for (AP_LIST::const_iterator it = ap_list.begin(); it < ap_list.end(); ++it)
        {
            QString name = it->name;

            if(!name.isEmpty())
            {
                tag = new RFTag();
                QString mac;

                mac += QString("%1").arg(it->mac_address.u[0], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[1], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[2], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[3], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[4], 2, 16);
                mac += QString(" - %1").arg(it->mac_address.u[5], 2, 16);

                tag->setName(it->name);
                tag->setId(mac);
                tag->setRSSI(it->rssi);

                rftags.append(tag);
            }
        }
    } catch (std::exception &e) {
         QMessageBox msgBox;
         msgBox.setText(e.what());
         msgBox.exec();
    }

    return &rftags;
}

void Processor::clearTagList()
{
    while (!rftags.isEmpty())
         delete rftags.takeFirst();

    rftags.clear();
}
