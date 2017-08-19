
#include "util.h"

#include "stdlib.h"


double doubleTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return 0.000001*tv.tv_usec + 1.0*tv.tv_sec;
}


double clamp(double x, double m, double M)
{
    if( x>M )
        x=M;

    if( x<m )
        x=m;

    return x;
}


double sCurve(double x)
{
    if(x>1.0) return 1.0;
    if(x<0.0) return 0.0;
    return 3*x*x-2*x*x*x;
}


std::string readFile(const std::string& fullpath)
{
    FILE* fp = fopen(fullpath.c_str(), "r");
    if( !fp )
    {
        printf( "file not found: %s\n", fullpath.c_str() );
        exit(0);
    }

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    char* data = (char*)malloc(size+1);
    data[size] = 0;
    fread(data, 1, size, fp);
    fclose(fp);

    std::string result(data);

    free(data);

    return result;
}


std::vector<std::string> components(const std::string& path, char separator)
{
    std::vector<std::string> result;

    std::string s;

    int n = path.size();
    for(int i = 0; i < n; i++)
    {
        char c = path[i];
        if( c == separator )
        {
            if( s.size() )
                result.push_back(s);
            s.clear();
        }
        else
            s += c;
    }

    if( s.size() )
        result.push_back(s);

    return result;
}

int stringToInt(const std::string& s)
{
    return atoi(s.c_str());
}

double stringToFloat(const std::string& s)
{
    return atof(s.c_str());
}

bool charInString(char c, const char* s)
{
    for(int i = 0; s[i]; i++)
        if( c == s[i] )
            return true;
    return false;
}

std::string flattenWhitespace(const std::string& ins)
{
    const char* s = ins.c_str();

    int n = strlen(s);
    char* r = new char[strlen(s)+1];

    char quotebegin = 0;
    bool escaped = false;

    int j = 0;
    for(int i = 0; i < n; i++)
    {
        char c = s[i];
        if( c == '\\' )
            escaped = true;
        if( !escaped && charInString(c, "\'\"") )
        {
            if(quotebegin)
                quotebegin = 0;
            else
                quotebegin = c;
        }
        if( !escaped && !quotebegin && charInString(c, "\t\n\t ") )
        {
            if( j != 0 && r[j-1]!=' ' )
                r[j++] = ' ';
        }
        else
            r[j++] = c;
    }
    r[j++] = 0;

    std::string result(r);
    delete r;

    return result;
}

