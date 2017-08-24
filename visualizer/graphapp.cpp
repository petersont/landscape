
#include "graphapp.h"

GraphApp::GraphApp(const std::string& path)
{
    std::string input = readFile(path);

    std::vector<std::string> lines = components(input, '\n');
    for( std::vector<std::string>::iterator itr = lines.begin(); itr != lines.end(); itr++ )
    {
        std::string& line(*itr);

        std::vector<std::string> lc = components( line, ',' );

        if( lc.size() == 3 )
        {
            nodes.push_back(
                Vector3d(
                    stringToFloat(flattenWhitespace(lc[0])),
                    stringToFloat(flattenWhitespace(lc[1])),
                    stringToFloat(flattenWhitespace(lc[2]))));
        }

        if( lc.size() == 2 )
        {
            edges.push_back(
                std::pair<int,int>( stringToInt(flattenWhitespace(lc[0])),
                      stringToInt(flattenWhitespace(lc[1]))));
        }
    }
}

void GraphApp::draw() const
{
    drawAxes();

    glColor3f(0, 0.5, 1);
    glPushMatrix();

    glBegin(GL_POINTS);
        for(std::vector<Vector3d>::const_iterator itr = nodes.begin(); itr!=nodes.end(); itr++)
            glVertex3f(itr->x, itr->y, itr->z);
    glEnd();


    glBegin(GL_LINES);
    for(std::vector<pair<int, int> >::const_iterator itr = edges.begin(); itr!=edges.end(); itr++)
    {
        const pair<int, int>& edge(*itr);
        int a = edge.first;
        int b = edge.second;
        glVertex3f(nodes[a].x, nodes[a].y, nodes[a].z);
        glVertex3f(nodes[b].x, nodes[b].y, nodes[b].z);
    }
    glEnd();

    glPopMatrix();
}

