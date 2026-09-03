
#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Goal() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_Goal__init(msg: *mut DoDishes_Goal) -> bool;
    fn robot_communication__action__DoDishes_Goal__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Goal>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_Goal__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Goal>);
    fn robot_communication__action__DoDishes_Goal__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_Goal>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Goal>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_Goal
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_Goal {
    /// Specify which dishwasher we want to use
    pub dishwasher_id: u32,

}



impl Default for DoDishes_Goal {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_Goal__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_Goal__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_Goal {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Goal__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Goal__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Goal__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_Goal {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_Goal where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_Goal";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Goal() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Result() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_Result__init(msg: *mut DoDishes_Result) -> bool;
    fn robot_communication__action__DoDishes_Result__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Result>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_Result__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Result>);
    fn robot_communication__action__DoDishes_Result__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_Result>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Result>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_Result
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_Result {

    // This member is not documented.
    #[allow(missing_docs)]
    pub total_dishes_cleaned: u32,

}



impl Default for DoDishes_Result {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_Result__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_Result__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_Result {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Result__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Result__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Result__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_Result {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_Result where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_Result";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Result() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Feedback() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_Feedback__init(msg: *mut DoDishes_Feedback) -> bool;
    fn robot_communication__action__DoDishes_Feedback__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Feedback>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_Feedback__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Feedback>);
    fn robot_communication__action__DoDishes_Feedback__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_Feedback>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_Feedback>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_Feedback
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_Feedback {

    // This member is not documented.
    #[allow(missing_docs)]
    pub percent_complete: f32,

}



impl Default for DoDishes_Feedback {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_Feedback__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_Feedback__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_Feedback {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Feedback__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Feedback__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_Feedback__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_Feedback {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_Feedback where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_Feedback";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_Feedback() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_FeedbackMessage() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_FeedbackMessage__init(msg: *mut DoDishes_FeedbackMessage) -> bool;
    fn robot_communication__action__DoDishes_FeedbackMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_FeedbackMessage>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_FeedbackMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_FeedbackMessage>);
    fn robot_communication__action__DoDishes_FeedbackMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_FeedbackMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_FeedbackMessage>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_FeedbackMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_FeedbackMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub feedback: super::super::action::rmw::DoDishes_Feedback,

}



impl Default for DoDishes_FeedbackMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_FeedbackMessage__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_FeedbackMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_FeedbackMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_FeedbackMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_FeedbackMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_FeedbackMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_FeedbackMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_FeedbackMessage where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_FeedbackMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_FeedbackMessage() }
  }
}




#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_SendGoal_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_SendGoal_Request__init(msg: *mut DoDishes_SendGoal_Request) -> bool;
    fn robot_communication__action__DoDishes_SendGoal_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Request>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_SendGoal_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Request>);
    fn robot_communication__action__DoDishes_SendGoal_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Request>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_SendGoal_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_SendGoal_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,


    // This member is not documented.
    #[allow(missing_docs)]
    pub goal: super::super::action::rmw::DoDishes_Goal,

}



impl Default for DoDishes_SendGoal_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_SendGoal_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_SendGoal_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_SendGoal_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_SendGoal_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_SendGoal_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_SendGoal_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_SendGoal_Request() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_SendGoal_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_SendGoal_Response__init(msg: *mut DoDishes_SendGoal_Response) -> bool;
    fn robot_communication__action__DoDishes_SendGoal_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Response>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_SendGoal_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Response>);
    fn robot_communication__action__DoDishes_SendGoal_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_SendGoal_Response>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_SendGoal_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_SendGoal_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub accepted: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub stamp: builtin_interfaces::msg::rmw::Time,

}



impl Default for DoDishes_SendGoal_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_SendGoal_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_SendGoal_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_SendGoal_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_SendGoal_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_SendGoal_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_SendGoal_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_SendGoal_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_SendGoal_Response() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_GetResult_Request() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_GetResult_Request__init(msg: *mut DoDishes_GetResult_Request) -> bool;
    fn robot_communication__action__DoDishes_GetResult_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Request>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_GetResult_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Request>);
    fn robot_communication__action__DoDishes_GetResult_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_GetResult_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Request>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_GetResult_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_GetResult_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub goal_id: unique_identifier_msgs::msg::rmw::UUID,

}



impl Default for DoDishes_GetResult_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_GetResult_Request__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_GetResult_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_GetResult_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_GetResult_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_GetResult_Request where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_GetResult_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_GetResult_Request() }
  }
}


#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_GetResult_Response() -> *const std::ffi::c_void;
}

#[link(name = "robot_communication__rosidl_generator_c")]
extern "C" {
    fn robot_communication__action__DoDishes_GetResult_Response__init(msg: *mut DoDishes_GetResult_Response) -> bool;
    fn robot_communication__action__DoDishes_GetResult_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Response>, size: usize) -> bool;
    fn robot_communication__action__DoDishes_GetResult_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Response>);
    fn robot_communication__action__DoDishes_GetResult_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DoDishes_GetResult_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<DoDishes_GetResult_Response>) -> bool;
}

// Corresponds to robot_communication__action__DoDishes_GetResult_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DoDishes_GetResult_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub result: super::super::action::rmw::DoDishes_Result,

}



impl Default for DoDishes_GetResult_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !robot_communication__action__DoDishes_GetResult_Response__init(&mut msg as *mut _) {
        panic!("Call to robot_communication__action__DoDishes_GetResult_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DoDishes_GetResult_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { robot_communication__action__DoDishes_GetResult_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DoDishes_GetResult_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DoDishes_GetResult_Response where Self: Sized {
  const TYPE_NAME: &'static str = "robot_communication/action/DoDishes_GetResult_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__robot_communication__action__DoDishes_GetResult_Response() }
  }
}






#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_communication__action__DoDishes_SendGoal() -> *const std::ffi::c_void;
}

// Corresponds to robot_communication__action__DoDishes_SendGoal
#[allow(missing_docs, non_camel_case_types)]
pub struct DoDishes_SendGoal;

impl rosidl_runtime_rs::Service for DoDishes_SendGoal {
    type Request = DoDishes_SendGoal_Request;
    type Response = DoDishes_SendGoal_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_communication__action__DoDishes_SendGoal() }
    }
}




#[link(name = "robot_communication__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__robot_communication__action__DoDishes_GetResult() -> *const std::ffi::c_void;
}

// Corresponds to robot_communication__action__DoDishes_GetResult
#[allow(missing_docs, non_camel_case_types)]
pub struct DoDishes_GetResult;

impl rosidl_runtime_rs::Service for DoDishes_GetResult {
    type Request = DoDishes_GetResult_Request;
    type Response = DoDishes_GetResult_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__robot_communication__action__DoDishes_GetResult() }
    }
}


