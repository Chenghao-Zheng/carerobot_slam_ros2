#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__LocalizationInfoBroadcast() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__LocalizationInfoBroadcast__init(msg: *mut LocalizationInfoBroadcast) -> bool;
    fn robot_communication__msg__LocalizationInfoBroadcast__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocalizationInfoBroadcast>, size: usize) -> bool;
    fn robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocalizationInfoBroadcast>);
    fn robot_communication__msg__LocalizationInfoBroadcast__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocalizationInfoBroadcast>, out_seq: *mut rosidl_runtime_rs::Sequence<LocalizationInfoBroadcast>) -> bool;
}

// Corresponds to robot_communication__msg__LocalizationInfoBroadcast
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 定位消息广播需要数据
/// 全局x位置

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocalizationInfoBroadcast {

    // This member is not documented.
    #[allow(missing_docs)]
    pub xposition: f32,

    /// 全局y位置
    pub yposition: f32,

    /// 全局x轴线速度
    pub xspeed: f32,

    /// 全局y轴线速度
    pub yspeed: f32,

    /// 车体x加速度
    pub xaccel: f32,

    /// 车体y加速度
    pub yaccel: f32,

    /// 底盘角度
    pub chassisangle: f32,

    /// 底盘角速度
    pub chassisgyro: f32,

    /// 时间戳
    pub timestamp: u32,

}



impl Default for LocalizationInfoBroadcast {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__LocalizationInfoBroadcast__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__LocalizationInfoBroadcast__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocalizationInfoBroadcast {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__LocalizationInfoBroadcast__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__LocalizationInfoBroadcast__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__LocalizationInfoBroadcast__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocalizationInfoBroadcast {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocalizationInfoBroadcast where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/LocalizationInfoBroadcast";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__LocalizationInfoBroadcast() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__ChassisControl() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__ChassisControl__init(msg: *mut ChassisControl) -> bool;
    fn robot_communication__msg__ChassisControl__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ChassisControl>, size: usize) -> bool;
    fn robot_communication__msg__ChassisControl__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ChassisControl>);
    fn robot_communication__msg__ChassisControl__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ChassisControl>, out_seq: *mut rosidl_runtime_rs::Sequence<ChassisControl>) -> bool;
}

// Corresponds to robot_communication__msg__ChassisControl
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

///  导航发布的消息
/// 全局x轴线速度

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ChassisControl {

    // This member is not documented.
    #[allow(missing_docs)]
    pub xspeed: f32,

    /// 全局y轴线速度
    pub yspeed: f32,

    /// 底盘角度
    pub chassisangle: f32,

    /// 底盘角速度
    pub chassisgyro: f32,

    /// 时间戳
    pub timestamp: u32,

    /// 标志位局部控制还是全局控制
    pub globalorlocal: bool,

}



impl Default for ChassisControl {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__ChassisControl__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__ChassisControl__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ChassisControl {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__ChassisControl__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__ChassisControl__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__ChassisControl__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ChassisControl {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ChassisControl where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/ChassisControl";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__ChassisControl() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__SensorData() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__SensorData__init(msg: *mut SensorData) -> bool;
    fn robot_communication__msg__SensorData__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SensorData>, size: usize) -> bool;
    fn robot_communication__msg__SensorData__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SensorData>);
    fn robot_communication__msg__SensorData__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SensorData>, out_seq: *mut rosidl_runtime_rs::Sequence<SensorData>) -> bool;
}

// Corresponds to robot_communication__msg__SensorData
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 接收到下位机发送的消息，轮速计、IMU、时间戳等
/// 局部速度

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SensorData {

    // This member is not documented.
    #[allow(missing_docs)]
    pub local_x_veloc: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub local_y_veloc: f32,

    /// 局部加速度
    pub local_x_accel: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub local_y_accel: f32,

    /// yaw轴数值
    pub yaw: f32,

    /// 时间戳 10us是时间戳的分辨率
    pub timestamp_10us: u32,

}



impl Default for SensorData {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__SensorData__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__SensorData__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SensorData {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__SensorData__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__SensorData__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__SensorData__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SensorData {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SensorData where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/SensorData";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__SensorData() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__Bspline() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__Bspline__init(msg: *mut Bspline) -> bool;
    fn robot_communication__msg__Bspline__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Bspline>, size: usize) -> bool;
    fn robot_communication__msg__Bspline__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Bspline>);
    fn robot_communication__msg__Bspline__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Bspline>, out_seq: *mut rosidl_runtime_rs::Sequence<Bspline>) -> bool;
}

// Corresponds to robot_communication__msg__Bspline
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Bspline {

    // This member is not documented.
    #[allow(missing_docs)]
    pub order: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub traj_id: i64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub knots: rosidl_runtime_rs::Sequence<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pts: rosidl_runtime_rs::Sequence<geometry_msgs::msg::rmw::Point>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_time: builtin_interfaces::msg::rmw::Time,

}



impl Default for Bspline {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__Bspline__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__Bspline__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Bspline {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Bspline__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Bspline__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Bspline__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Bspline {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Bspline where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/Bspline";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__Bspline() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__EsdfMap() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__EsdfMap__init(msg: *mut EsdfMap) -> bool;
    fn robot_communication__msg__EsdfMap__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EsdfMap>, size: usize) -> bool;
    fn robot_communication__msg__EsdfMap__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EsdfMap>);
    fn robot_communication__msg__EsdfMap__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EsdfMap>, out_seq: *mut rosidl_runtime_rs::Sequence<EsdfMap>) -> bool;
}

// Corresponds to robot_communication__msg__EsdfMap
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 栅格地图的原点x值(相对世界坐标系),单位为m

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EsdfMap {

    // This member is not documented.
    #[allow(missing_docs)]
    pub origin_x: f32,

    /// 栅格地图的原点y值(相对世界坐标系),单位为m
    pub origin_y: f32,

    /// 栅格地图的分辨率
    pub resolution: f32,

    /// 栅格地图的宽
    pub width: f32,

    /// 栅格地图的高
    pub height: f32,

    /// 一维数组，数组内的数据表示为对应栅格的占用概率。
    /// 栅格地图中每一个小格的坐标对应一维数组中的一个数据。
    /// 栅格数据大小代表当前点到障碍物的距离数值
    /// -值表示未知区域
    pub data: rosidl_runtime_rs::Sequence<i32>,

}



impl Default for EsdfMap {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__EsdfMap__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__EsdfMap__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EsdfMap {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__EsdfMap__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__EsdfMap__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__EsdfMap__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EsdfMap {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EsdfMap where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/EsdfMap";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__EsdfMap() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__Goal() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__msg__Goal__init(msg: *mut Goal) -> bool;
    fn robot_communication__msg__Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Goal>, size: usize) -> bool;
    fn robot_communication__msg__Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Goal>);
    fn robot_communication__msg__Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<Goal>) -> bool;
}

// Corresponds to robot_communication__msg__Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// 目标点信息
/// x位置信息

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Goal {

    // This member is not documented.
    #[allow(missing_docs)]
    pub position_x: f32,

    /// y位置信息
    pub position_y: f32,

    /// yaw轴角度信息
    pub position_yaw: f32,

}



impl Default for Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__msg__Goal__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__msg__Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__msg__Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Goal where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/msg/Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__msg__Goal() }
  }
}


