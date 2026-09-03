#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to robot_communication__msg__LocalizationInfoBroadcast
/// 定位消息广播需要数据
/// 全局x位置

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::LocalizationInfoBroadcast::default())
  }
}

impl rosidl_runtime_rs::Message for LocalizationInfoBroadcast {
  type RmwMsg = super::msg::rmw::LocalizationInfoBroadcast;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        xposition: msg.xposition,
        yposition: msg.yposition,
        xspeed: msg.xspeed,
        yspeed: msg.yspeed,
        xaccel: msg.xaccel,
        yaccel: msg.yaccel,
        chassisangle: msg.chassisangle,
        chassisgyro: msg.chassisgyro,
        timestamp: msg.timestamp,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      xposition: msg.xposition,
      yposition: msg.yposition,
      xspeed: msg.xspeed,
      yspeed: msg.yspeed,
      xaccel: msg.xaccel,
      yaccel: msg.yaccel,
      chassisangle: msg.chassisangle,
      chassisgyro: msg.chassisgyro,
      timestamp: msg.timestamp,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      xposition: msg.xposition,
      yposition: msg.yposition,
      xspeed: msg.xspeed,
      yspeed: msg.yspeed,
      xaccel: msg.xaccel,
      yaccel: msg.yaccel,
      chassisangle: msg.chassisangle,
      chassisgyro: msg.chassisgyro,
      timestamp: msg.timestamp,
    }
  }
}


// Corresponds to robot_communication__msg__ChassisControl
///  导航发布的消息
/// 全局x轴线速度

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ChassisControl::default())
  }
}

impl rosidl_runtime_rs::Message for ChassisControl {
  type RmwMsg = super::msg::rmw::ChassisControl;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        xspeed: msg.xspeed,
        yspeed: msg.yspeed,
        chassisangle: msg.chassisangle,
        chassisgyro: msg.chassisgyro,
        timestamp: msg.timestamp,
        globalorlocal: msg.globalorlocal,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      xspeed: msg.xspeed,
      yspeed: msg.yspeed,
      chassisangle: msg.chassisangle,
      chassisgyro: msg.chassisgyro,
      timestamp: msg.timestamp,
      globalorlocal: msg.globalorlocal,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      xspeed: msg.xspeed,
      yspeed: msg.yspeed,
      chassisangle: msg.chassisangle,
      chassisgyro: msg.chassisgyro,
      timestamp: msg.timestamp,
      globalorlocal: msg.globalorlocal,
    }
  }
}


// Corresponds to robot_communication__msg__SensorData
/// 接收到下位机发送的消息，轮速计、IMU、时间戳等
/// 局部速度

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SensorData::default())
  }
}

impl rosidl_runtime_rs::Message for SensorData {
  type RmwMsg = super::msg::rmw::SensorData;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        local_x_veloc: msg.local_x_veloc,
        local_y_veloc: msg.local_y_veloc,
        local_x_accel: msg.local_x_accel,
        local_y_accel: msg.local_y_accel,
        yaw: msg.yaw,
        timestamp_10us: msg.timestamp_10us,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      local_x_veloc: msg.local_x_veloc,
      local_y_veloc: msg.local_y_veloc,
      local_x_accel: msg.local_x_accel,
      local_y_accel: msg.local_y_accel,
      yaw: msg.yaw,
      timestamp_10us: msg.timestamp_10us,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      local_x_veloc: msg.local_x_veloc,
      local_y_veloc: msg.local_y_veloc,
      local_x_accel: msg.local_x_accel,
      local_y_accel: msg.local_y_accel,
      yaw: msg.yaw,
      timestamp_10us: msg.timestamp_10us,
    }
  }
}


// Corresponds to robot_communication__msg__Bspline

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub knots: Vec<f64>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pts: Vec<geometry_msgs::msg::Point>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub start_time: builtin_interfaces::msg::Time,

}



impl Default for Bspline {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Bspline::default())
  }
}

impl rosidl_runtime_rs::Message for Bspline {
  type RmwMsg = super::msg::rmw::Bspline;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        order: msg.order,
        traj_id: msg.traj_id,
        knots: msg.knots.into(),
        pts: msg.pts
          .into_iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        start_time: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.start_time)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      order: msg.order,
      traj_id: msg.traj_id,
        knots: msg.knots.as_slice().into(),
        pts: msg.pts
          .iter()
          .map(|elem| geometry_msgs::msg::Point::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        start_time: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.start_time)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      order: msg.order,
      traj_id: msg.traj_id,
      knots: msg.knots
          .into_iter()
          .collect(),
      pts: msg.pts
          .into_iter()
          .map(geometry_msgs::msg::Point::from_rmw_message)
          .collect(),
      start_time: builtin_interfaces::msg::Time::from_rmw_message(msg.start_time),
    }
  }
}


// Corresponds to robot_communication__msg__EsdfMap
/// 栅格地图的原点x值(相对世界坐标系),单位为m

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub data: Vec<i32>,

}



impl Default for EsdfMap {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::EsdfMap::default())
  }
}

impl rosidl_runtime_rs::Message for EsdfMap {
  type RmwMsg = super::msg::rmw::EsdfMap;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        origin_x: msg.origin_x,
        origin_y: msg.origin_y,
        resolution: msg.resolution,
        width: msg.width,
        height: msg.height,
        data: msg.data.into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      origin_x: msg.origin_x,
      origin_y: msg.origin_y,
      resolution: msg.resolution,
      width: msg.width,
      height: msg.height,
        data: msg.data.as_slice().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      origin_x: msg.origin_x,
      origin_y: msg.origin_y,
      resolution: msg.resolution,
      width: msg.width,
      height: msg.height,
      data: msg.data
          .into_iter()
          .collect(),
    }
  }
}


// Corresponds to robot_communication__msg__Goal
/// 目标点信息
/// x位置信息

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Goal::default())
  }
}

impl rosidl_runtime_rs::Message for Goal {
  type RmwMsg = super::msg::rmw::Goal;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        position_x: msg.position_x,
        position_y: msg.position_y,
        position_yaw: msg.position_yaw,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      position_x: msg.position_x,
      position_y: msg.position_y,
      position_yaw: msg.position_yaw,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      position_x: msg.position_x,
      position_y: msg.position_y,
      position_yaw: msg.position_yaw,
    }
  }
}


