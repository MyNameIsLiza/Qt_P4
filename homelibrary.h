#ifndef HOMELIBRARY_H
#define HOMELIBRARY_H

#include <QApplication>
#include <QList>

class HomeLibrary
{
private:
    int id;
    QString title;
    QString author;
    QString publish_year;
    QString genre;
public:

    int get_id(){
        return id;
    }
    void set_id(int Id){
        id = Id;
    }
    QString get_title(){
        return title;
    }
    void set_title(QString Title){
        title = Title;
    }
    QString get_author(){
        return author;
    }
    void set_author(QString Author){
        author = Author;
    }
    QString get_publish_year(){
        return publish_year;
    }
    void set_publish_year(QString Publish_year){
        publish_year = Publish_year;
    }
    QString get_genre(){
        return genre;
    }
    void set_genre(QString Genre){
        genre = Genre;
    }
    HomeLibrary(){
    };
    HomeLibrary(QString Title, QString Author, QString Publish_year, QString Genre){
        title = Title;
        author = Author;
        publish_year = Publish_year;
        genre = Genre;
    };

    static QList<HomeLibrary> search_by_author(QList<HomeLibrary> books, QString s){

        QList<HomeLibrary> search;
        foreach(HomeLibrary book, books){
            if(book.author == s){
                search.append(book);
            }
        }
        return search;
    };

    static QList<HomeLibrary> search_by_genre(QList<HomeLibrary> books, QString s){

        QList<HomeLibrary> search;
        foreach(HomeLibrary book, books){
            if(book.genre == s){
                search.append(book);
            }
        }
        return search;
    };

    static QList<HomeLibrary> search_by_publish_year(QList<HomeLibrary> books, QString s){

        QList<HomeLibrary> search;
        foreach(HomeLibrary book, books){
            if(book.publish_year == s){
                search.append(book);
            }
        }
        return search;
    };
    static HomeLibrary search_by_id(QList<HomeLibrary> books, qsizetype id){

        HomeLibrary search;
        foreach(HomeLibrary book, books){
            if(book.id == id){
                search = book;
            }
        }
        return search;
    };

    static bool compare_by_id (HomeLibrary i,HomeLibrary j) { return (i.get_id()<j.get_id()); }
    static bool compare_by_author (HomeLibrary i,HomeLibrary j) { return (i.get_author()<j.get_author()); }
    static bool compare_by_publish_year (HomeLibrary i,HomeLibrary j) { return (i.get_publish_year()<j.get_publish_year()); }
    static bool compare_by_genre (HomeLibrary i,HomeLibrary j) { return (i.get_genre()<j.get_genre()); }
};


#endif // HOMELIBRARY_H
