/*
 * Licensed to the University of Washington under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The University of Washington
 * licenses this file to you under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef __atl06_dispatch__
#define __atl06_dispatch__

/******************************************************************************
 * INCLUDES
 ******************************************************************************/

#include "MsgQ.h"
#include "LuaObject.h"
#include "RecordObject.h"
#include "DispatchObject.h"
#include "OsApi.h"
#include "MsgQ.h"
#include "MathLib.h"

/******************************************************************************
 * ATL06 DISPATCH CLASS
 ******************************************************************************/

class Atl06Dispatch: public DispatchObject
{
    public:

        /*--------------------------------------------------------------------
         * Constants
         *--------------------------------------------------------------------*/

        static const char* LuaMetaName;
        static const struct luaL_Reg LuaMetaTable[];

        /*--------------------------------------------------------------------
         * Types
         *--------------------------------------------------------------------*/

        typedef enum {
            STAGE_AVG = 0,
            STAGE_LSF = 1,
            NUM_STAGES = 2
        } stages_t;

        typedef struct {
            uint32_t    h5atl03_rec_cnt;
            uint32_t    algo_out_cnt[NUM_STAGES];
            uint32_t    post_success_cnt;
            uint32_t    post_dropped_cnt;
        } stats_t;

        /*--------------------------------------------------------------------
         * Methods
         *--------------------------------------------------------------------*/

        static int  luaCreate   (lua_State* L);

    private:

        /*--------------------------------------------------------------------
         * Data
         *--------------------------------------------------------------------*/

        Publisher*  outQ;
        stats_t     stats;
        stages_t    stages;

        /*--------------------------------------------------------------------
         * Methods
         *--------------------------------------------------------------------*/

                        Atl06Dispatch           (lua_State* L, const char* otuq_name);
                        ~Atl06Dispatch          (void);

        bool            processRecord           (RecordObject* record, okey_t key) override;

        double          averageHeightStage      (RecordObject* record, okey_t key);
        MathLib::lsf_t  leastSquaresFitStage    (RecordObject* record, okey_t key);

        static int      luaStats                (lua_State* L);
        static int      luaSelect               (lua_State* L);
};

#endif  /* __atl06_dispatch__ */