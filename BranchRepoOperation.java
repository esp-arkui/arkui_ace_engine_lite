package com.huawei.operation;


import com.huawei.entity.pojo.CodeCheckResultSummaryVo;
import com.huawei.entity.vo.codecheck.BranchRepo.BranchRepo;
import com.huawei.enums.CodeCheckCollectionName;
import com.huawei.utils.OperationUtil;
import com.mongodb.client.result.UpdateResult;
import org.apache.commons.collections4.CollectionUtils;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.data.domain.Sort;
import org.springframework.data.mongodb.core.MongoTemplate;
import org.springframework.data.mongodb.core.aggregation.Aggregation;
import org.springframework.data.mongodb.core.aggregation.AggregationOperation;
import org.springframework.data.mongodb.core.aggregation.LookupOperation;
import org.springframework.data.mongodb.core.query.Criteria;
import org.springframework.data.mongodb.core.query.Query;
import org.springframework.data.mongodb.core.query.Update;
import org.springframework.stereotype.Component;

import java.util.*;
import java.util.stream.Collectors;

@Component
public class BranchRepoOperation {

    @Autowired
    @Qualifier("codeCheckMongoTemplate")
    private MongoTemplate mongoTemplate;

    /**
     * 批量插入数据
     */
    public void insertBranchAndRepo(List<BranchRepo> BranchRepos) {
        mongoTemplate.insert(BranchRepos, BranchRepo.class);
    }

    /**
     * 获取所有有仓库属性的仓
     */
    public List<BranchRepo> getRepoAttrs() {
        return mongoTemplate.find(Query.query(Criteria.where("repo_attrs").exists(true)), BranchRepo.class);
    }


    /**
     * 获得限制数量的任务id
     */
    public List<BranchRepo> getLimitedTaskId() {
        Criteria exists = Criteria.where("codecheck_task_id").ne("").and("execute_time").exists(false);
        Criteria lte = Criteria.where("codecheck_task_id").ne("").and("execute_time").lte(getToday());
        Criteria criteria = new Criteria();
        Query query = new Query(criteria.orOperator(exists, lte)).limit(10);
        return mongoTemplate.find(query, BranchRepo.class);
    }

    private Date getToday() {
        Calendar today = Calendar.getInstance();
        today.set(Calendar.HOUR_OF_DAY, 0);
        today.set(Calendar.MINUTE, 0);
        today.set(Calendar.SECOND, 0);
        today.set(Calendar.MILLISECOND, 0);
        return today.getTime();
    }


    /**
     * 根据repoUrl repoBranchName更新taskId
     */
    public boolean updateTaskId(String repoUrl, String repoBranchName, String taskId, String parentTaskId) {
        Update updateTaskId = Update.update("codecheck_task_id", taskId);
        updateTaskId.set("parent_task_id", parentTaskId);
        Query repUrl = new Query(Criteria.where("repo_url").is(repoUrl).and("repo_branch_name").is(repoBranchName));
        return mongoTemplate.upsert(repUrl, updateTaskId, BranchRepo.class).wasAcknowledged();
    }

    /**
     * 获得所有的数据
     */
    public List<BranchRepo> getAll() {
        int page = 0;
        int size = 1000;
        int count = 0;
        List<BranchRepo> result = new ArrayList<>();

        do {
            page++;
            Query query = new Query();
            query.skip((page - 1) * size).limit(size);
            List<BranchRepo> branchRepos =
                    mongoTemplate.find(query, BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
            count = branchRepos.size();
            result.addAll(branchRepos);
        } while (count == size);

        return result;
    }

    /**
     * 根据repoRul repoBranchName 更新项目名称，manifest分支名称
     */
    public void updateBranchReps(BranchRepo branchRepo) {
        Query query = new Query(Criteria.where("repo_url").is(branchRepo.getRepoUrl())
                .and("repo_branch_name").is(branchRepo.getRepoBranchName()));

        Update update = Update.update("manifest_branch_name", branchRepo.getManifestBranchName());

        if (CollectionUtils.isNotEmpty(branchRepo.getRepoAttrs())) {
            update.set("repo_attrs", branchRepo.getRepoAttrs());
        }

        mongoTemplate.updateFirst(query, update, BranchRepo.class);
    }

    /**
     * 根据repoUrl 和repoBranchName删除数据
     *
     * @param repoUrl        仓的url
     * @param repoBranchName 该仓的分支名称
     *                       不含有check_type字段信息的删除
     */
    public void deleteByUrlAndRepoBranchName(String repoUrl, String repoBranchName) {
        Query query = new Query(Criteria.where("repo_url").is(repoUrl)
                .and("repo_branch_name").is(repoBranchName).and("check_type").exists(false));
        mongoTemplate.remove(query, BranchRepo.class).wasAcknowledged();
    }

    /**
     * 批量删除
     *
     * @param branchRepos
     */
    public void deleteByList(List<BranchRepo> branchRepos) {
        if (branchRepos.size() == 0) {
            return;
        }
        Criteria[] criteriaArray = new Criteria[branchRepos.size()];
        criteriaArray[0] = Criteria.where("repo_url").is(branchRepos.get(0).getRepoUrl())
                .and("repo_branch_name").is(branchRepos.get(0).getRepoBranchName());
        for (int i = 1; i < branchRepos.size(); i++) {
            criteriaArray[i] = Criteria.where("repo_url").is(branchRepos.get(i).getRepoUrl())
                    .and("repo_branch_name").is(branchRepos.get(i).getRepoBranchName());
        }

        Query query = new Query(criteriaArray[0].orOperator(criteriaArray));
        mongoTemplate.remove(query, BranchRepo.class);
    }

    /**
     * 通过id集合进行批量删除
     */
    public void batchDeleteByIds(List<String> ids) {
        Criteria criteria = Criteria.where("_id").in(ids);
        mongoTemplate.remove(Query.query(criteria), CodeCheckCollectionName.BRANCH_REPO);
    }









    /**
     * 根据仓库分支和地址查询仓库信息
     *
     * @param repoBranch 仓库分支
     * @param repoUrl    仓库地址
     * @return {@link BranchRepo}
     **/
    public BranchRepo query(String repoBranch, String repoUrl) {
        return mongoTemplate.findOne(
                Query.query(Criteria.where("repo_branch_name").is(repoBranch).and("repo_url").is(repoUrl)),
                BranchRepo.class);
    }


    /**
     * 根据taskId查询仓库分支信息
     *
     * @param taskId taskId
     * @return {@link BranchRepo}
     */
    public BranchRepo getByTaskId(String taskId) {
        return mongoTemplate.findOne(Query.query(Criteria.where("codecheck_task_id").is(taskId)), BranchRepo.class);
    }

    /**
     * 执行后更新最后的执行时间
     *
     * @param taskId
     */
    public void updateExecTimeByTaskId(String taskId) {
        Criteria criteria = Criteria.where("codecheck_task_id").is(taskId);
        Query query = new Query(criteria);
        Update executeTime = Update.update("execute_time", Calendar.getInstance().getTime());
        mongoTemplate.upsert(query, executeTime, BranchRepo.class);
    }

    public List<String> getRepos(String projectName, String branchName) {
        Criteria criteria = Criteria.where("project_name").is(projectName);
        criteria.and("manifest_branch_name").is(branchName);
        List<BranchRepo> branchRepos = mongoTemplate.find(Query.query(criteria), BranchRepo.class);
        return branchRepos.stream().map(BranchRepo::getRepoName).distinct().collect(Collectors.toList());
    }

    public long removeAllTaskId() {
        Criteria criteria = Criteria.where("codecheck_task_id").ne("");
        Query query = Query.query(criteria);
        Update update = Update.update("codecheck_task_id", "");
        return mongoTemplate.updateMulti(query, update, BranchRepo.class).getModifiedCount();

    }

    /**
     * 根据条件获取仓库信息
     *
     * */
    public BranchRepo getRepoByBasicInfo(String repoName, String gitUrl, String targetBranch) {
        Query query = Query.query(Criteria.where("repo_name").is(repoName)
                .and("repo_url").is(gitUrl).and("repo_branch_name").is(targetBranch));
        return mongoTemplate.findOne(query, BranchRepo.class);
    }

    public List<String> getParentTaskId(String repoName, String projectName, String repoUrl) {
        Criteria criteria = Criteria.where("repo_name").is(repoName)
                .and("projectName").is(projectName).and("repo_url").is(repoUrl)
                .and("parent_task_id").exists(true).ne("").ne(null);
        Query query = Query.query(criteria);
        List<BranchRepo> branchRepos = mongoTemplate.find(query, BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
        if (CollectionUtils.isEmpty(branchRepos)) {
            return Collections.EMPTY_LIST;
        }
        return branchRepos.stream().map(BranchRepo::getParentTaskId).collect(Collectors.toList());
    }

    /**
     * 2021.9.16新功能适配老数据  后续可以删除
     *
     * @param branchRepo
     */
    public void updateProjectId(BranchRepo branchRepo) {
        Query query = new Query(Criteria.where("repo_url").is(branchRepo.getRepoUrl())
                .and("repo_branch_name").is(branchRepo.getRepoBranchName()));
        Update update = Update.update("project_Id", branchRepo.getProjectId());
        mongoTemplate.updateFirst(query, update, BranchRepo.class);

    }

    /**
     * 获取指定仓库所有的分支
     */
    public List<String> getRepoBranches(String projectName, String branchName, String repoName) {
        Criteria criteria = Criteria.where("project_name").is(projectName);
        criteria.and("manifest_branch_name").is(branchName);
        criteria.and("repo_name").is(repoName);

        return OperationUtil.getFieldList("repo_branch_name", criteria, mongoTemplate, CodeCheckCollectionName.BRANCH_REPO);
    }

    /**
     * 获取所有的仓库
     */
    public List<String> getAllRepo() {
        return OperationUtil.getFieldList("repo_name", Criteria.where("repo_name").exists(true), mongoTemplate,
                CodeCheckCollectionName.BRANCH_REPO);
    }

    /**
     * 根据项目名称查询每日检查的代码仓库的名称
     *
     * @param projectName 项目名称
     */
    public List<String> getBranchRepoName(String projectName) {
        Query query = new Query(Criteria.where("project_name").is(projectName).and("enable_daily_check").is(true));
        return mongoTemplate.find(query, BranchRepo.class).stream().map(BranchRepo::getRepoName).collect(Collectors.toList());
    }

    public List<BranchRepo> getByProjectName(String openHarmony) {
        Criteria criteria = Criteria.where("project_name").is(openHarmony);
        Query query = Query.query(criteria);
        return mongoTemplate.find(query, BranchRepo.class);

    }

    public List<String> getReposByCondition(String project, String branch) {
        Criteria criteria = Criteria.where("project_name").is(project).and("repo_branch_name").is(branch);
        Query query = Query.query(criteria);
        return mongoTemplate.find(query, BranchRepo.class).stream().map(BranchRepo::getRepoName).collect(Collectors.toList());
    }

    /**
     * 通过项目名和分支名获取指定仓库数据
     *
     * @author lwx1021041
     * @since 2022-02-21
     */
    public List<BranchRepo> getByProjectAndBranch(String project, String branch) {
        Criteria criteria = Criteria.where("project_name").is(project).and("repo_branch_name").is(branch);
        return mongoTemplate.find(Query.query(criteria), BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
    }

    /**
     * 获取当前任务的父任务
     *
     * @return
     **/
    public BranchRepo getCurrentTaskParentTaskId(String taskId) {
        Criteria criteria = Criteria.where("codecheck_task_id").is(taskId);
        return mongoTemplate.findOne(Query.query(criteria), BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
    }

    /**
     * 查询某一项目下所有已经创建任务的仓库
     *
     * @param projectId
     * @return
     */
    public List<BranchRepo> getRepoByProjectId(String projectId) {
        Criteria criteria = Criteria.where("codecheck_task_id").exists(true).ne("");
        Query query = Query.query(criteria);
        query.fields().include("codecheck_task_id").include("repo_url").include("repo_branch_name");
        return mongoTemplate.find(query, BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
    }


    public boolean updateOne(CodeCheckResultSummaryVo summaryVo) {
        Criteria criteria = Criteria.where("_id").exists(true);
        if (StringUtils.isNotBlank(summaryVo.getProjectName())) {
            criteria.and("project_name").is(summaryVo.getProjectName());
        }
        if (StringUtils.isNotBlank(summaryVo.getRepoNameEn())) {
            criteria.and("repo_name").is(summaryVo.getRepoNameEn());
        }
        if (StringUtils.isNotBlank(summaryVo.getGitBranch())) {
            criteria.and("repo_branch_name").is(summaryVo.getGitBranch());
        }
        Update update = Update.update("codecheck_task_id", summaryVo.getTaskId());
        UpdateResult updateResult = mongoTemplate.updateMulti(Query.query(criteria), update, CodeCheckCollectionName.BRANCH_REPO);
        System.out.println(updateResult);
        return updateResult.wasAcknowledged();
    }

    /**
     * 根据任务id更新每日代码检查开关
     *
     * @param id               数据id
     * @param enableDailyCheck 是否进行每日代码检查
     * @return boolean 是否更新成功
     */
    public boolean updateTaskEnableDailyCheck(String id, boolean enableDailyCheck) {
        Query query = Query.query(Criteria.where("_id").is(id));
        Update update = Update.update("enable_daily_check", enableDailyCheck);
        UpdateResult updateResult = mongoTemplate.updateFirst(query, update, BranchRepo.class);
        return updateResult.wasAcknowledged() && updateResult.getModifiedCount() != 0;
    }

    public List<BranchRepo> getAllProjectAndRepo() {
        Query query = new Query();
        query.fields().include("project_name").include("repo_branch_name").include("repo_name");
        return mongoTemplate.find(query, BranchRepo.class);
    }


    public List<BranchRepo> getByProjectAndRepoName(String projectName, String repoName) {
        Criteria criteria = Criteria.where("project_name").is(projectName);
        if (StringUtils.isNotEmpty(repoName)) {
            criteria.and("repo_name").is(repoName);
        }
        return mongoTemplate.find(Query.query(criteria), BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);
    }

    /**
     * 更新当前创建的任务的父任务id
     * 同时更新当前已经创建好的任务的taskid
     */
    public void updateCurrentRepo(String targetBranch, String gitUrl, String repoName, String parentTaskId, String taskId) {
        Criteria criteria = Criteria.where("repo_url").is(gitUrl).and("repo_branch_name").is(targetBranch).and("repo_name").is(repoName);
        Update updateTaskId = Update.update("codecheck_task_id", taskId)
                .set("parent_task_id", parentTaskId);
        mongoTemplate.updateFirst(Query.query(criteria), updateTaskId, BranchRepo.class, CodeCheckCollectionName.BRANCH_REPO);

    }
}
