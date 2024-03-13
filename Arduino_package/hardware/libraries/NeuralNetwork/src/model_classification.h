#ifndef MODEL_CLASSIFICATION_H
#define MODEL_CLASSIFICATION_H

#include "module_vipnn.h"

extern nnmodel_t img_classification;

extern int classification_preprocess(void *data_in, nn_data_param_t *data_param, void *tensor_in, nn_tensor_param_t *tensor_param);
extern int classification_postprocess(void *tensor_out, nn_tensor_param_t *param, void *res);

#endif
