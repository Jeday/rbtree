#include "text_stat.h"


class comp{
    public:
    bool operator()(const std::pair<int,std::string>& t,const std::pair<int,std::string>& t2){
        return t.first>t2.first;
    }
};

void stat_book(std::string path){
    std::ifstream file;
    multiset<std::string> book;
    file.open(path);
    if(!file.is_open())
     return;
    QRegExp rx("(\\s|\\,|\\.|\\:|\\t|\\(|\\)|\\{|\\})");
    std::string line;
    while (std::getline(file,line)) {
           QStringList list;
           list = QString::fromStdString(line).split(rx,QString::SkipEmptyParts);
           foreach (QString s, list) {
                    book.insert(s.toLower().toStdString());
               }
        }

    Priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> pq;
    auto it =book.begin();

    while (it!=book.end()) {
            pq.push({it.count(),*it});
            book.erase(*it);
            it = book.begin();
        }

    pq.sort();
    std::ofstream output;
    output.open("/home/je_day/Documents/rbtree/log.txt");
    if (true)
        for(int i = 0;i<20;++i){
            output<<pq.top().second<<'\t'<<pq.top().first<<"\n";
            pq.pop();
        }

}





