#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <tf/transform_datatypes.h>
#include <crcl_cpp/CRCLProgramInstanceClasses.hh>
#include "crcl_app/crcl_program_instance_handler.h"

// globals needed by the XML parser
extern CRCLProgramFile * CRCLProgramTree;
extern FILE * yyin;
extern int yyparse();
extern void yylex_destroy();

#define DEFINE_DEFAULT_HANDLER(TYPE)					\
static int default_ ## TYPE ## _handler(TYPE * t)			\
{									\
  printf("" #TYPE "\n");						\
  return 0;								\
}									\
static int (* TYPE ## _handler)(TYPE *) = default_ ## TYPE ## _handler; \
int crcl_program_instance_handler_register_ ## TYPE (int (*func)(TYPE * t)) \
{									\
  TYPE ## _handler = func;						\
}

DEFINE_DEFAULT_HANDLER(ActuateJointsType);
DEFINE_DEFAULT_HANDLER(CloseToolChangerType);
DEFINE_DEFAULT_HANDLER(ConfigureJointReportsType);
DEFINE_DEFAULT_HANDLER(DwellType);
DEFINE_DEFAULT_HANDLER(GetStatusType);
DEFINE_DEFAULT_HANDLER(MessageType);
DEFINE_DEFAULT_HANDLER(MoveScrewType);
DEFINE_DEFAULT_HANDLER(MoveThroughToType);
DEFINE_DEFAULT_HANDLER(MoveToType);
DEFINE_DEFAULT_HANDLER(OpenToolChangerType);
DEFINE_DEFAULT_HANDLER(RunProgramType);
DEFINE_DEFAULT_HANDLER(SetAngleUnitsType);
DEFINE_DEFAULT_HANDLER(SetEndEffectorParametersType);
DEFINE_DEFAULT_HANDLER(SetEndEffectorType);
DEFINE_DEFAULT_HANDLER(SetEndPoseToleranceType);
DEFINE_DEFAULT_HANDLER(SetForceUnitsType);
DEFINE_DEFAULT_HANDLER(SetIntermediatePoseToleranceType);
DEFINE_DEFAULT_HANDLER(SetLengthUnitsType);
DEFINE_DEFAULT_HANDLER(SetMotionCoordinationType);
DEFINE_DEFAULT_HANDLER(SetRobotParametersType);
DEFINE_DEFAULT_HANDLER(SetRotAccelType);
DEFINE_DEFAULT_HANDLER(SetRotSpeedType);
DEFINE_DEFAULT_HANDLER(SetTorqueUnitsType);
DEFINE_DEFAULT_HANDLER(SetTransAccelType);
DEFINE_DEFAULT_HANDLER(SetTransSpeedType);
DEFINE_DEFAULT_HANDLER(StopMotionType);

#define CALL_IT(TYPE, FUNC) (* TYPE ## _handler)(FUNC)

int crcl_program_instance_handler_init(FILE *inFile)
{
  yyin = inFile;
  yyparse();

  return 0;
}

int crcl_program_instance_handler_run(void)
{
  printf("InitCanonType(%d)\n", CRCLProgramTree->CRCLProgram->InitCanon->CommandID->val);
  
  for (std::list<MiddleCommandType *>::iterator iter = CRCLProgramTree->CRCLProgram->MiddleCommand->begin(); iter != CRCLProgramTree->CRCLProgram->MiddleCommand->end(); iter++) {
#define DO_IT(TYPE)					\
    if (dynamic_cast<TYPE *>(*iter)) {			\
      CALL_IT(TYPE, dynamic_cast<TYPE *>(*iter));	\
      continue;						\
    }
    DO_IT(ActuateJointsType);
    DO_IT(CloseToolChangerType);
    DO_IT(ConfigureJointReportsType);
    DO_IT(DwellType);
    DO_IT(GetStatusType);
    DO_IT(MessageType);
    DO_IT(MoveScrewType);
    DO_IT(MoveThroughToType);
    DO_IT(MoveToType);
    DO_IT(OpenToolChangerType);
    DO_IT(RunProgramType);
    DO_IT(SetAngleUnitsType);
    DO_IT(SetEndEffectorParametersType);
    DO_IT(SetEndEffectorType);
    DO_IT(SetEndPoseToleranceType);
    DO_IT(SetForceUnitsType);
    DO_IT(SetIntermediatePoseToleranceType);
    DO_IT(SetLengthUnitsType);
    DO_IT(SetMotionCoordinationType);
    DO_IT(SetRobotParametersType);
    DO_IT(SetRotAccelType);
    DO_IT(SetRotSpeedType);
    DO_IT(SetTorqueUnitsType);
    DO_IT(SetTransAccelType);
    DO_IT(SetTransSpeedType);
    DO_IT(StopMotionType);
    // else unknown type
  }

  printf("EndCanonType(%d)\n", CRCLProgramTree->CRCLProgram->EndCanon->CommandID->val);
}

int crcl_program_instance_handler_exit(void)
{  
  delete CRCLProgramTree;
  yylex_destroy();
  return 0;
}
