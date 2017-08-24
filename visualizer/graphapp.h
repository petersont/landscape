#ifndef _GRAPHAPP_
#define _GRAPHAPP_

#include "panapp.h"


class GraphApp : public PanApp
{
public:
    GraphApp(const std::string& path);
    virtual ~GraphApp() {}

protected:
    std::vector<Vector3d> nodes;
    std::vector<pair<int,int> > edges;

    void draw() const;
};


#endif
