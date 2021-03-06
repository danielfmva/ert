from ert.cwrap import clib, CWrapper
from ert.enkf.data.enkf_node import EnkfNode
from ert.enkf.enums.enkf_state_type_enum import EnkfStateType
from ert.enkf.node_id import NodeId
from ert.test import ErtTestContext
from ert.test.extended_testcase import ExtendedTestCase
from ert.util import BoolVector

test_lib  = clib.ert_load("libenkf")
cwrapper =  CWrapper(test_lib)

get_active_mask = cwrapper.prototype("bool_vector_ref gen_data_config_get_active_mask( gen_data_config )")
update_active_mask = cwrapper.prototype("void gen_data_config_update_active( gen_data_config, int, bool_vector)")

class GenDataTest(ExtendedTestCase):
    def setUp(self):
        self.config_file = self.createTestPath("Statoil/config/with_GEN_DATA/config")


    def test_create(self):
        with ErtTestContext("gen_data_test", self.config_file) as test_context:
            ert = test_context.getErt()
            fs1 =  ert.getEnkfFsManager().getCurrentFileSystem()
            config_node = ert.ensembleConfig().getNode("TIMESHIFT")

            data_node = EnkfNode(config_node)
            data_node.tryLoad(fs1, NodeId(60, 0, EnkfStateType.FORECAST))

            gen_data = data_node.asGenData()
            data = gen_data.getData()

            self.assertEqual(len(data) , 2560)
            
            
            
