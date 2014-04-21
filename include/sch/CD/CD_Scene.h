#ifndef _CD_SCENE
#define _CD_SCENE

#pragma once



#include <vector>
#include <sch/sch_api.h>
#include <sch/S_Object/S_Object.h>
#include <sch/CD/CD_Pair.h>


namespace sch
{
  class CD_Scene
  {
  public:
    sch_API CD_Scene(void);
    sch_API virtual ~CD_Scene(void);

    /*!
    * \brief Add Object to scene, returns an index that must be kept for collision detection
    */
    sch_API int addObject(S_Object* O);

    /*!
    * \brief Withdraw an object
    */
    sch_API void withdrawObject( int a);

    sch_API void ignorePair( int a, int b);

    sch_API void considerPair( int a, int b);

    sch_API CD_Pair* operator()( int a, int b) const
    {
      if (a!=b)
      {
        return (b<a)? pairs_[a][b]:pairs_[b][a];
      }
      else
        return NULL;
    }


    sch_API int  sceneProximityQuery();

    sch_API S_Object * operator[](unsigned char i)const
    {
      return objects_[i];
    }

    sch_API size_t size()
    {
      return objects_.size();
    }


    /*!
    *\brief Doesn't Compute the closest points, just gives the result of last computations.
    */
    sch_API Scalar getWitnessPoints(int a, int b,Point3 &p1,Point3 &p2)
    {
      if (a!=b)
      {
        if (b<a)
        {
          p1=witness_[a][b];
          p2=witness_[b][a];
          return distances_[a][b];
        }
        else
        {
          p1=witness_[b][a];
          p2=witness_[a][b];
          return distances_[b][a];
        }
      }
      else
      {
        return 0;
      }
    }


  protected:
    std::vector <S_Object*> objects_;

    std::vector <std::vector <CD_Pair*> > pairs_;

    std::vector <std::vector <Point3 > > witness_;

    std::vector <std::vector <Scalar > > distances_;
  };
}
#endif