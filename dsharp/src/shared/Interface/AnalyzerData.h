// Class automatically generated by Dev-C++ New Class wizard

#ifndef ANALYZERDATA_H
#define ANALYZERDATA_H

#include <BigInt.hpp>

//#include <Interface/Assignment.h>
#include "../src_sharpSAT/Basics.h"

#include <vector>

#include <iostream>
#include <fstream>

#include <string.h>


using namespace std;

enum DATA_IDX
{

    AVG_DEC_LEV  = 0,  // average decision Level
    AVG_CONFLICT_LEV, // average conflict Level
    AVG_SOLUTION_LEV, // average solution Level

    LONGEST_CCL_lastUIP, // longest conflict clause by last UIP scheme
    AVG_CCL_lastUIP, // avg conflict clause length by last UIP scheme
    LONGEST_CCL_1stUIP, // longest conflict clause by 1st UIP scheme
    AVG_CCL_1stUIP,  // avg conflict clause length by 1st UIP scheme

    FCACHE_MAXMEM,  // Formula Cache Memoery Bound
    FCACHE_MEMUSE,  // Formula Cache memory usage
    FCACHE_USEDBUCKETS, // number of hashbuckets used
    FCACHE_CACHEDCOMPS,
    FCACHE_RETRIEVALS, // number of retrieved components
    FCACHE_INCLUDETRIES, // number of times it was tried to put a component into the cache
    XX_MAX_IDX
};

/// strings describing the data identified by DATA_IDX
static const char * doubleDataDesc[] =
{
    "avg dec dl","avg conflict dl","avg solution dl","longest ccl lastUIP","avg ccl lastUIP","longest ccl firstUIP","avg ccl firstUIP",
    "cacher memory bound", "cache mem-usage","cache used buckets","cache cached components","cache retrievals", "cache include tries","NOTHING"
};


enum INT_DATA_ID
{
    NVARS =  0,  // num Of Vars
    NUSED_VARS,
    NORIGINAL_CLAUSES,
    NREMOVED_CLAUSES,
    NADDED_CLAUSES,
    NRECEIVED_ASS,  // int nReceivedSatAssignments;
    NCONFLICTS, // int nConflicts;
    NIMPLICATIONS, // int nImplications;
    NIBCPIMPLS,
    NPROCESSED_COMPS, // int nProcessedComponents;
    MAX_DL, // int maxDecLevel;
    MAX_SOL_DL, // int maxSolutionLevel;
    NDECISIONS, // int nDecisions;
    INT_MAX_ID
};

/// strings describing the data identified by INT_DATA_ID
static const char * intDataDesc[] =
{
    "variables","used vars","original clauses","removed clauses","added clauses",
    "received sat assignments", "conflicts","implications","ibcpimplications","processed components",
    "max dl","max solution dl","decisions","NOTHING"
};


enum ID_DATA
{
    DECISION,
    CONFLICT,
    SOLUTION,
    IMPLICATION,
    IBCPIMPL,
    CCL_lastUIP, // conflict clause by last UIP scheme
    CCL_1stUIP //  conflict clause by 1st UIP scheme


//XX_MAX_IDX = 7
};



class AnalyzerData
{
public:
    double elapsedTime;

    SOLVER_StateT theExitState;
    /// Zahl der Variablen der Instanz
    int nVars;

    /// Zahl der Variablen, die tats�hlich in Klauseln vorkommen
    int nUsedVars;

    /// Klauselzahl
    int nOriginalClauses;

    int nRemovedClauses;

    int nAddedClauses;

    // Zahl der erfllenden Belegungen, die bergeben wurden
    // sollte Kleiner sein, als die Zahl der eigentlichen L�ungen
    int nReceivedSatAssignments;

    /// Anzahl aller getroffenen Entscheidungen
    int nDecisions;

    /// Zahl aller gefundenen Implikationen
    int nImplications;

    int nImplicitImplications;

    /// Zahl aller w�rend der Suche aufgetretenen Konflikte
    int nConflicts;


    /// insgesamt bearbeitete Komponenten
    int nProcessedComponents;

    /// maximaler Decision level
    int maxDecLevel;
    int maxSolutionLevel;

    vector<double> evalData;
    BigInt countSAT;

    // class constructor
    AnalyzerData();
    // class destructor
    ~AnalyzerData();

    /// setzt alle Werte auf Null zurck (nur intern wichtig).
    void init();

    BigInt getAllAssignments() const
    {
        return pow(BigInt(2),nVars);
    }

    BigInt getNumSatAssignments() const
    {
        return countSAT;
    }

    void printNumSatAss_whole() const
    {
        toSTDOUT(countSAT.to_string());
    }


    double get(DATA_IDX dataID) const
    {
        return evalData[dataID];
    }

    unsigned int getI(INT_DATA_ID idataID) const;

    bool setI(INT_DATA_ID idataID, int val);

    void set(DATA_IDX dataID, double val)
    {
        evalData[dataID] = val;
    }


    void finishcountSATAnalysis();

    void writeToFile(const char *lpcstrFileName) const;
    void loadFromFile(const char *lpcstrFileName);
};
/*@}*/

/** \addtogroup RunAnalyze Laufanalyse
 * \ingroup Interna
 */
/*@{*/
class CRunAnalyzer
{
    AnalyzerData theData;

    bool first;

protected:

    //bool includeInPrBackBone(CAssignment &s,double nSols);


public:

    // class constructor
    CRunAnalyzer();
    // class destructor
    ~CRunAnalyzer();

    const AnalyzerData &getData() const;

    AnalyzerData &changeableData()
    {
        return theData;
    }

    void init(int nVars, int nClauses);

    //void setUsedVars(const set<int> &rUsedVars);

    void setUsedVars(unsigned int nUsedVars);

    void setRemovedClauses(int rClauses)
    {
        theData.nRemovedClauses = rClauses;
    }

    void addValue(ID_DATA dataID, int actDecLevel = 0, double someData = 0.0);

    void setValue(DATA_IDX dataIDX, double someData);

    void addClause();

    void setSatCount(const BigInt  &codedSols) {
        theData.countSAT = codedSols;
    }



    void setExitState(SOLVER_StateT st)
    {
        theData.theExitState = st;
    }
    void setElapsedTime(double timeV)
    {
        theData.elapsedTime = timeV;
    }

    // No description
    void finishcountSATAnalysis();
};
#endif // CANALYZERDATA_H
