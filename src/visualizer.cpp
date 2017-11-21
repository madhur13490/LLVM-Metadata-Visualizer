#include<fstream>
#include<iostream>
#include<regex>
#include<assert.h>

using namespace std;

bool isSupported(string s)
{
    if (s.find("DILocation") != string::npos          || \
        s.find("DILexicalBlock") != string::npos      || \
        s.find("DILocalVariable") != string::npos     || \
        s.find("DIBasicType") != string::npos         || \
        s.find("DICompositeType") != string::npos     || \
        s.find("DIDerivedType") != string::npos       || \
        s.find("DISubprogram") != string::npos) return true;
    else return false;
}

string emitHTMLTitle(string sourceNode, string s)
{
    assert(isSupported(s));

    std::regex attributes(R"(([a-zA-Z0-9_! ]+)[(]{1}(.+)[)]{1})");
    std::regex split(R"((\w+)[:]{1}([a-zA-Z0-9!""_ ]+))");
    std::sregex_iterator end;
    string tableString = "<TABLE>", tableTitle="";

    std::sregex_iterator iter1(s.begin(), s.end(), attributes);
    while(iter1 != end)
    {
        if (iter1->size() > 1) {
            tableTitle = (*iter1)[1];
            tableTitle = tableTitle.erase(0, 1);
            tableString += "<TR><TD>" + sourceNode + "</TD>" + "<TD>" + tableTitle + "</TD></TR>";

            std::string dest = (*iter1)[2];
            std::sregex_iterator iter2(dest.begin(), dest.end(), split);
            while (iter2 != end) {
                if (iter2->size() > 1) {
                   tableString += "<TR>";
                   tableString += "<TD>"; tableString += (*iter2)[1]; tableString += "</TD>";
                   tableString += "<TD>"; tableString += (*iter2)[2]; tableString += "</TD>";
                   tableString += "</TR>";
                }      
                ++iter2;
            }
        }
        ++iter1;
    }
    tableString += "</TABLE>";
    return tableString;
}

int main(int argc, char** argv)
{
    std::regex e(R"(^!\d+)");
    std::ifstream infile(argv[1]);
    std::ofstream outfile(argv[2]);
    std::string line;
    std::string strippedLine, sourceNode;
    int number = 0;
  
    if (argc < 3) {
        cout << "You seemed to miss an argument. Syntax is \"filename.out IRfileName.ll DotFile.dot\"" << endl;
        exit(0);
    }
 
    if (!infile) {
        cout << "File not found.\n";
        exit(1);
    } else {
        outfile << "graph IRGraph {\n";
    }

    while (getline(infile, line)) {
        std::sregex_iterator iter(line.begin(), line.end(), e);
        std::sregex_iterator end;

        if (iter != end) {
            sourceNode = (*iter)[0];
            strippedLine = sourceNode.erase(0, 1);

            std::size_t i = line.find("=");
            std::string sub = line.substr(i+1);
            if (isSupported(sub)) { 
                outfile << strippedLine << " [label=<" << emitHTMLTitle(sourceNode, sub) <<">]\n";
            } else { 
                outfile << strippedLine << " [label=<" << line << "<BR/>>]" << endl;
            }
        
            // regex to get pointees.
            std::regex vertices(R"(!\d+)");
            std::sregex_iterator iter1(sub.begin(), sub.end(), vertices);

            while(iter1 != end) {
                for(unsigned i = 0; i < iter1->size(); ++i) {
                    string dest = (*iter1)[i]; 
                    outfile << sourceNode << " -- " << dest.erase(0, 1) << ";" << endl;
                }
                ++iter1;
            }
         } else {
            continue;
         }
    }
    outfile << "}" << endl;
    return 0;
}
