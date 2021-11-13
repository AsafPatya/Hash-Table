#ifndef COURSESMANAGER_H_
#define COURSESMANAGER_H_

#include "TCL.h"
#include "RankTree.h"
#include "HashTable.h"
#include "DynamicArray.h"

//Struct Course implements a course with a dynamic array for his lectures
struct Course
{
    int courseID;
    int numOfLectures;
    DynamicArray lectures;
    Course(int id):courseID(id),numOfLectures(0),lectures(){}
    Course():courseID(0),numOfLectures(0),lectures(){}
    ~Course(){}
};

//Class CourseManager manages all the data structure we need
class CoursesManager{
public:
    //Compares courses by thier ID
    class CompareCourse{
        public:
	    int operator()(Course c1,Course c2){
            return c1.courseID-c2.courseID;
        }
        int operator()(int courseID,Course c){
            return courseID-c.courseID;
        }
        int operator()(Course c,int courseID){
            return c.courseID-courseID;
        }
    };

    HashTable<Course> courseTable; //Hash-Table containing all the courses

    RankTree<TCL,CompareLecture> TCLTree; //Rank Tree containing all the lectures with more than zero views

    int totalLectures; //Sum of all the lectures in all courses

    CoursesManager();

    ~CoursesManager();

    bool AddCourse(int courseID);

    bool RemoveCourse(int courseID);

    bool AddClass(int courseID, int* lectureID);
    
    bool WatchClass(int courseID,int lectureID,int time,bool* lectureExists);

    bool TimeViewed(int courseID,int lectureID,int* timeViewed,bool* lectureExists);

    bool GetIthMostViewedClass(int i, int *courseID, int *lectureID);
};
#endif