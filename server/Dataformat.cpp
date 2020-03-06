#include "Dataformat.h"

void DataFormat(QByteArray data, Data*  temp)
{

    if(!data.isEmpty()){
        temp->data.clear();
        int count=1;
        for(auto a = data.begin()+1;(*a)!=MID;a++)
        {
            temp->pid.push_back(*a);
            count++;
        }
        for(auto a = data.begin()+count+1;(*a)!=END;a++)
        {
            temp->data.push_back(*a);
            count++;
        }
    }


}
