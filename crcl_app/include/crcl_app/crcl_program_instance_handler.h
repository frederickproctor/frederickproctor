#ifndef CRCL_PROGRAM_INSTANCE_HANDLER_H
#define CRCL_PROGRAM_INSTANCE_HANDLER_H

#include <stdio.h>

extern int crcl_program_instance_handler_init(FILE *inFile);
extern int crcl_program_instance_handler_run(void);
extern int crcl_program_instance_handler_exit(void);

#define DECLARE_REGISTRAR(TYPE) extern int crcl_program_instance_handler_register_ ## TYPE (int (*)(TYPE * t))

DECLARE_REGISTRAR(ActuateJointsType);
DECLARE_REGISTRAR(CloseToolChangerType);
DECLARE_REGISTRAR(ConfigureJointReportsType);
DECLARE_REGISTRAR(DwellType);
DECLARE_REGISTRAR(GetStatusType);
DECLARE_REGISTRAR(MessageType);
DECLARE_REGISTRAR(MoveScrewType);
DECLARE_REGISTRAR(MoveThroughToType);
DECLARE_REGISTRAR(MoveToType);
DECLARE_REGISTRAR(OpenToolChangerType);
DECLARE_REGISTRAR(RunProgramType);
DECLARE_REGISTRAR(SetAngleUnitsType);
DECLARE_REGISTRAR(SetEndEffectorParametersType);
DECLARE_REGISTRAR(SetEndEffectorType);
DECLARE_REGISTRAR(SetEndPoseToleranceType);
DECLARE_REGISTRAR(SetForceUnitsType);
DECLARE_REGISTRAR(SetIntermediatePoseToleranceType);
DECLARE_REGISTRAR(SetLengthUnitsType);
DECLARE_REGISTRAR(SetMotionCoordinationType);
DECLARE_REGISTRAR(SetRobotParametersType);
DECLARE_REGISTRAR(SetRotAccelType);
DECLARE_REGISTRAR(SetRotSpeedType);
DECLARE_REGISTRAR(SetTorqueUnitsType);
DECLARE_REGISTRAR(SetTransAccelType);
DECLARE_REGISTRAR(SetTransSpeedType);
DECLARE_REGISTRAR(StopMotionType);

#define crcl_program_instance_handler_register(TYPE, FUNC) crcl_program_instance_handler_register_ ## TYPE (FUNC)

#endif	/* CRCL_PROGRAM_INSTANCE_HANDLER_H */
