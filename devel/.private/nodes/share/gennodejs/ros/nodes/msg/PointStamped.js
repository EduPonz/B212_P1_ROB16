// Auto-generated. Do not edit!

// (in-package nodes.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');
let Point = require('./Point.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class PointStamped {
  constructor() {
    this.header = new std_msgs.msg.Header();
    this.point = new Point();
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type PointStamped
    // Serialize message field [header]
    bufferInfo = std_msgs.msg.Header.serialize(obj.header, bufferInfo);
    // Serialize message field [point]
    bufferInfo = Point.serialize(obj.point, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type PointStamped
    let tmp;
    let len;
    let data = new PointStamped();
    // Deserialize message field [header]
    tmp = std_msgs.msg.Header.deserialize(buffer);
    data.header = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [point]
    tmp = Point.deserialize(buffer);
    data.point = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'nodes/PointStamped';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c63aecb41bfdfd6b7e1fac37c7cbe7bf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    Point point
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    # 0: no frame
    # 1: global frame
    string frame_id
    
    ================================================================================
    MSG: nodes/Point
    float64 x
    float64 y
    float64 z
    
    `;
  }

};

module.exports = PointStamped;
