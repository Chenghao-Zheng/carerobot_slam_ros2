// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_communication:action/DoDishes.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__BUILDER_HPP_
#define ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_communication/action/detail/do_dishes__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_Goal_dishwasher_id
{
public:
  Init_DoDishes_Goal_dishwasher_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_communication::action::DoDishes_Goal dishwasher_id(::robot_communication::action::DoDishes_Goal::_dishwasher_id_type arg)
  {
    msg_.dishwasher_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_Goal>()
{
  return robot_communication::action::builder::Init_DoDishes_Goal_dishwasher_id();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_Result_total_dishes_cleaned
{
public:
  Init_DoDishes_Result_total_dishes_cleaned()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_communication::action::DoDishes_Result total_dishes_cleaned(::robot_communication::action::DoDishes_Result::_total_dishes_cleaned_type arg)
  {
    msg_.total_dishes_cleaned = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_Result>()
{
  return robot_communication::action::builder::Init_DoDishes_Result_total_dishes_cleaned();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_Feedback_percent_complete
{
public:
  Init_DoDishes_Feedback_percent_complete()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_communication::action::DoDishes_Feedback percent_complete(::robot_communication::action::DoDishes_Feedback::_percent_complete_type arg)
  {
    msg_.percent_complete = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_Feedback>()
{
  return robot_communication::action::builder::Init_DoDishes_Feedback_percent_complete();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_SendGoal_Request_goal
{
public:
  explicit Init_DoDishes_SendGoal_Request_goal(::robot_communication::action::DoDishes_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::robot_communication::action::DoDishes_SendGoal_Request goal(::robot_communication::action::DoDishes_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_SendGoal_Request msg_;
};

class Init_DoDishes_SendGoal_Request_goal_id
{
public:
  Init_DoDishes_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DoDishes_SendGoal_Request_goal goal_id(::robot_communication::action::DoDishes_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DoDishes_SendGoal_Request_goal(msg_);
  }

private:
  ::robot_communication::action::DoDishes_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_SendGoal_Request>()
{
  return robot_communication::action::builder::Init_DoDishes_SendGoal_Request_goal_id();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_SendGoal_Response_stamp
{
public:
  explicit Init_DoDishes_SendGoal_Response_stamp(::robot_communication::action::DoDishes_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::robot_communication::action::DoDishes_SendGoal_Response stamp(::robot_communication::action::DoDishes_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_SendGoal_Response msg_;
};

class Init_DoDishes_SendGoal_Response_accepted
{
public:
  Init_DoDishes_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DoDishes_SendGoal_Response_stamp accepted(::robot_communication::action::DoDishes_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_DoDishes_SendGoal_Response_stamp(msg_);
  }

private:
  ::robot_communication::action::DoDishes_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_SendGoal_Response>()
{
  return robot_communication::action::builder::Init_DoDishes_SendGoal_Response_accepted();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_GetResult_Request_goal_id
{
public:
  Init_DoDishes_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_communication::action::DoDishes_GetResult_Request goal_id(::robot_communication::action::DoDishes_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_GetResult_Request>()
{
  return robot_communication::action::builder::Init_DoDishes_GetResult_Request_goal_id();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_GetResult_Response_result
{
public:
  explicit Init_DoDishes_GetResult_Response_result(::robot_communication::action::DoDishes_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::robot_communication::action::DoDishes_GetResult_Response result(::robot_communication::action::DoDishes_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_GetResult_Response msg_;
};

class Init_DoDishes_GetResult_Response_status
{
public:
  Init_DoDishes_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DoDishes_GetResult_Response_result status(::robot_communication::action::DoDishes_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_DoDishes_GetResult_Response_result(msg_);
  }

private:
  ::robot_communication::action::DoDishes_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_GetResult_Response>()
{
  return robot_communication::action::builder::Init_DoDishes_GetResult_Response_status();
}

}  // namespace robot_communication


namespace robot_communication
{

namespace action
{

namespace builder
{

class Init_DoDishes_FeedbackMessage_feedback
{
public:
  explicit Init_DoDishes_FeedbackMessage_feedback(::robot_communication::action::DoDishes_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::robot_communication::action::DoDishes_FeedbackMessage feedback(::robot_communication::action::DoDishes_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_communication::action::DoDishes_FeedbackMessage msg_;
};

class Init_DoDishes_FeedbackMessage_goal_id
{
public:
  Init_DoDishes_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DoDishes_FeedbackMessage_feedback goal_id(::robot_communication::action::DoDishes_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_DoDishes_FeedbackMessage_feedback(msg_);
  }

private:
  ::robot_communication::action::DoDishes_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_communication::action::DoDishes_FeedbackMessage>()
{
  return robot_communication::action::builder::Init_DoDishes_FeedbackMessage_goal_id();
}

}  // namespace robot_communication

#endif  // ROBOT_COMMUNICATION__ACTION__DETAIL__DO_DISHES__BUILDER_HPP_
