#pragma once

#include <stdexcept>

namespace bank::storage::exceptions
{
struct InvalidJsonDocumentWithTransaction : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

}