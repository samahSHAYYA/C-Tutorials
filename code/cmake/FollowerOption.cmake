function(define_follower_option FOLLOWED_OPTION FOLLOWER_OPTION
                             FOLLOWER_OPTION_DESCRIPTION)
# Function: define_follower_option(FOLLOWED_OPTION FOLLOWER_OPTION
#                                  FOLLOWER_OPTION_DESCRIPTION)
#
# This function sets the default value of a given followed option and defines a
# follower option that follows the state of the followed option. The follower
# option will take on the value of the followed option until it is manually set
# by the user. The function assumes that the FOLLOWED_OPTION is already defined.
# Otherwise, it would cause a fatal error.
#
# Arguments:
#   FOLLOWED_OPTION: The name of the option to be followed.
#   FOLLOWER_OPTION: The name of the follower option.
#   FOLLOWER_OPTION_DESCRIPTION: The description of the follower option.
#
# Example usage:
#   define_follower_option(BUILD_SHARED
#                          MY_PROJECT_BUILD_SHARED
#                          "Build shared libraries for my project")
#
#   This will define the MY_PROJECT_BUILD_SHARED option that follows the state
#   of BUILD_SHARED option. If MY_PROJECT_BUILD_SHARED is not set manually, it
#   will take on the value of BUILD_SHARED until MY_PROJECT_BUILD_SHARED is
#   defined by the user.

  # Checking if FOLLOWED_OPTION is not defined
  if (NOT DEFINED FOLLOWED_OPTION)
    message(FATAL_ERROR "${FOLLOWED_OPTION} is not defined!")
  endif()

  # If the follower option is not defined in the cache, unset it and define it
  # with a default value that follows the followed option
  if(NOT DEFINED ${FOLLOWER_OPTION})
    set(${FOLLOWER_OPTION} ${${FOLLOWED_OPTION}} CACHE BOOL
        ${FOLLOWER_OPTION_DESCRIPTION} FORCE
    )
  endif()

  # Make sure the follower option follows the state of the followed option
  set(${FOLLOWER_OPTION} ${${FOLLOWED_OPTION}} PARENT_SCOPE)
endfunction()
