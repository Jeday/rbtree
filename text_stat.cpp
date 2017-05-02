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
    QRegExp rx("(\\s|\\,|\'|\"|\\.|\\:|\\t|\\(|\\)|\\{|\\})");
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
    //std::string rng = "ring";
    //std::cout<< book.find(rng).count();
    std::ofstream output;
    output.open("D:/User/desktop/rbtree-master/log.txt");
    if (output.is_open())
        output<<"Top words used in "+path<<std::endl;
        int cnt = 1;
        while(!pq.empty()){
            cnt++;
            output<<pq.top().second<<'\t'<<pq.top().first<<"\n";
            if (cnt % 100 == 0)
                std::cout<<cnt<<" words written"<<std::endl;
            pq.pop();
        }

}


void name_stat_book(std::string path){
    std::ifstream file;
    multiset<std::string> book;
    multiset<std::string> other_words;
    file.open(path);
    if(!file.is_open())
     return;
    QRegExp rx("(\\s|\\,|\'|\"|\\.|\\:|\\t|\\(|\\)|\\{|\\})");
    std::string line;
    while (std::getline(file,line)) {
           QStringList list;
           list = QString::fromStdString(line).split(rx,QString::SkipEmptyParts);
           foreach (QString s, list) {
                if (!(s[0].isUpper()))
                    other_words.insert(s.toStdString());
                else
                    book.insert(s.toStdString());
           }


        }

    auto _it = other_words.begin();
    while(_it != other_words.end()){
        QString s = QString::fromStdString(*_it);
        s[0] = s[0].toUpper();


        auto b_it = book.find(s.toStdString());
        if (b_it != book.end())
            book.erase(*b_it);
        other_words.erase(*_it);
        _it = other_words.begin();
    }




    Priority_queue<std::pair<int,std::string>,std::vector<std::pair<int,std::string>>,comp> pq;
    auto it =book.begin();

    while (it!=book.end()) {
            pq.push({it.count(),*it});
            book.erase(*it);
            it = book.begin();
        }
    //std::string rng = "ring";
    //std::cout<< book.find(rng).count();
    std::ofstream output;
    output.open("D:/User/desktop/rbtree-master/name_log.txt");
    if (output.is_open())
        output<<"Top names used in "+path<<std::endl;
        int cnt = 1;
        while(!pq.empty()){
            cnt++;
            output<<pq.top().second<<'\t'<<pq.top().first<<"\n";
            if (cnt % 100 == 0)
                std::cout<<cnt<<" words written"<<std::endl;
            pq.pop();
        }

}




