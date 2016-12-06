// Auto-generated. Do not edit!

// (in-package nodes.msg)


"use strict";

let _serializer = require('../base_serialize.js');
let _deserializer = require('../base_deserialize.js');
let _finder = require('../find.js');

//-----------------------------------------------------------

class Point {
  constructor() {
    this.x = 0.0;
    this.y = 0.0;
    this.z = 0.0;
  }

  static serialize(obj, bufferInfo) {
    // Serializes a message object of type Point
    // Serialize message field [x]
    bufferInfo = _serializer.float64(obj.x, bufferInfo);
    // Serialize message field [y]
    bufferInfo = _serializer.float64(obj.y, bufferInfo);
    // Serialize message field [z]
    bufferInfo = _serializer.float64(obj.z, bufferInfo);
    return bufferInfo;
  }

  static deserialize(buffer) {
    //deserializes a message object of type Point
    let tmp;
    let len;
    let data = new Point();
    // Deserialize message field [x]
    tmp = _deserializer.float64(buffer);
    data.x = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [y]
    tmp = _deserializer.float64(buffer);
    data.y = tmp.data;
    buffer = tmp.buffer;
    // Deserialize message field [z]
    tmp = _deserializer.float64(buffer);
    data.z = tmp.data;
    buffer = tmp.buffer;
    return {
      data: data,
      buffer: buffer
    }
  }

  static datatype() {
    // Returns string type for a message object
    return 'nodes/Point';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '4a842b65f413084dc2b10fb484ea7f17';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float64 x
    float64 y
    float64 z
    
    `;
  }

};

module.exports = Point;
