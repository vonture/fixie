#include "fixie/exceptions.hpp"
#include "fixie_lib/context.hpp"
#include "fixie_lib/debug.hpp"

namespace fixie
{
    void handle_entry_point_exception()
    {
        try
        {
            throw;
        }
        catch (const fixie::gl_error& e)
        {
            fixie::log_gl_error(e);
        }
        catch (const fixie::context_error& e)
        {
            fixie::log_context_error(e);
        }
        catch (...)
        {
            UNREACHABLE();
        }
    }
}
