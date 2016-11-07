#ifndef _BEES_SERIAL_EVENTS_H_
#define _BEES_SERIAL_EVENTS_H_

enum serialMsgTypes {
  eSerialMsg_debug,
  eSerialMsg_dumpIns,
  eSerialMsg_insDump,
  eSerialMsg_dumpParams,
  eSerialMsg_paramsDump,
  eSerialMsg_triggerParam,
  eSerialMsg_triggerIn,
  eSerialMsg_queryIn,
  eSerialMsg_inVal,
  eSerialMsg_queryParam,
  eSerialMsg_paramVal,
  eSerialMsg_outVal,

  //messages for patching bees
  eSerialMsg_dumpOutputs,
  eSerialMsg_outputsDump,
  eSerialMsg_dumpConnections,
  eSerialMsg_connectionsDump,
  eSerialMsg_connect,
  eSerialMsg_disconnect,
  eSerialMsg_dumpOps,
  eSerialMsg_opsDump,
  eSerialMsg_dumpOpDescriptions,
  eSerialMsg_opDescriptionsDump,
  eSerialMsg_newOp,
  eSerialMsg_deleteOp,

  //Messages for preset store/recall
  eSerialMsg_storePreset,
  eSerialMsg_recallPreset,

  //Messages for serial bfin prog
  eSerialMsg_bfinProgStart,
  eSerialMsg_bfinHexChunk,
  eSerialMsg_bfinDscChunk,
  eSerialMsg_bfinProgEnd,
  eSerialMsg_bfinProgEcho,
  eSerialMsg_numParams
};

#endif
