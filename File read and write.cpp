#include <iostream>
#include <fstream>
#include<string>
using namespace std;

int main() {

    ofstream outFile("CV.txt");
    if (outFile.is_open())
    {

        outFile <<" Md Readwanul Hoq Chowdhury\n";
        outFile <<" Hajibari, Kuratoli, Khilkhet, Dhaka\n";
        outFile <<" Contact No: 01708652876\n";
        outFile <<" Email: readwanulhoq@gmail.com\n \n";
        outFile <<" PERSONAL DETAILS\n";
        outFile <<"   Full name         : Md Readwanul Hoq Chowdhury\n";
        outFile <<"   Father’s Name     : Md. Abdul Haque Chowdhury\n";
        outFile <<"   Mother’s Name     : Ranuara Begum\n";
        outFile <<"   Date of Birth     : 16st October ,1996\n";
        outFile <<"   Present Address   : Hajibari, Kuratoli, Khilkhet, Dhaka\n";
        outFile <<"   Permanent Address : C-4/J, AFCCL Housing Colony, Ashuganj, Brahmanbaria\n";
        outFile <<"   Religion          : Muslim\n";
        outFile <<"   Blood Group       : A (+)\n\n";
        outFile <<" EDUCATION\n";
        outFile <<"   * Secondary School Certificate(SSC)\n";
        outFile <<"     Ashuganj Sarkarkhana School and College\n";
        outFile <<"     2014 – 2016|| GPA: 4.79 (science)\n";
        outFile <<"   * Higher Secondary Certificate(HSC)\n";
        outFile <<"     Ashuganj Sarkarkhana School and College\n";
        outFile <<"     2016– 2018 || GPA: 4.67(science)\n";
        outFile <<"   * Bachelor of Science in Computer Science and Engineering\n";
        outFile <<"     American International University of Bangladesh\n";
        outFile <<"     2018-2022|| CGPA: 3.56\n\n";
        outFile <<" WORK EXPERIENCE\n";
        outFile <<"    * Jr. System Support at AIUB || 2020-2021\n";
        outFile <<"    * Marn Stack Developer as Freelancer|| 2021-2022\n";
        outFile <<"   Nascenia Company\n";
        outFile <<"    * Developed clean and well-structured OOP Code\n";
        outFile <<"    * Designed and implemented cloud infrastructure using AWS and Azure\n\n";
        outFile <<" SKILLS\n";
        outFile <<"   * Microsoft Office Management: Word, Excel, PowerPoint, SPSS\n";
        outFile <<"   * Software development       : C, C++, JAVA, C#(.net), TypeScript, R, Kotlin\n";
        outFile <<"   * Online Based Programming   : HTML5, XML, ASP (.net), Angular, CSS3\n\n";
        outFile <<" COMMUNICATION\n";
        outFile <<"   * Excellent in both verbal and writing in English & Bengali\n";
        outFile <<"   * Experienced in delivering presentations and reports to colleagues and clients.\n\n";
        outFile <<" INTEREST & ACTIVITIES\n";
        outFile <<"   * Playing Cricket\n";
        outFile <<"   * Listening Music\n";
        outFile <<"   * Watching Movies\n";

        outFile.close();
    }

    ifstream File("CV.txt");
    if (File.is_open())
    {
        string line;

        while (getline(File, line)) {
        cout << line << endl;
    }
    }

    return 0;
}

