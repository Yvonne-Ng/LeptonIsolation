#ifndef TRACK_WRITER_H
#define TRACK_WRITER_H

// forward declare HDF5 things
namespace H5 {
    class Group;
}
namespace H5Utils {
    class VariableFillers;
    class WriterXd;
}

// forward declare EDM things
namespace xAOD {
    class TrackParticle_v1;
    typedef TrackParticle_v1 TrackParticle;
}

// EDM includes
#include "xAODTracking/TrackParticleContainer.h"

class TrackWriter
{
    public:
        // constructor: the writer will create the output dataset in some group
        TrackWriter(H5::Group& output_group);

        // destructor (takes care of flushing output file too)
        ~TrackWriter();

        // we want to disable copying and assignment, it's not trivial to
        // make this play well with output files
        TrackWriter(TrackWriter&) = delete;
        TrackWriter operator=(TrackWriter&) = delete;

        // function that's actually called to write the event
        void write(const xAOD::TrackParticleContainer& tracks);

    private:
        // the functions that fill the output need to be defined when the
        // class is initialized. They will fill from this track pointer, which
        // must be updated each time we wright.
        std::vector<const xAOD::TrackParticle*> m_current_tracks;
        std::vector<size_t> m_track_idx;

        // The writer itself
        H5Utils::WriterXd* m_writer;
};

#endif
